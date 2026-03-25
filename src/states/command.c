#include <ncurses.h>
#include <string.h>

#include "../core/appstate.h"
#include "command.h"
#include "states.h"
#include "../commands/command-funcs.h"


#define COMMAND_WIN_WIDTH 50
#define COMMAND_WIN_HEIGTH 3

char command[256];
WINDOW *CommandWin;
u8 position;



void CommandEnter(struct AppState *as) {
	// creeate command window
	CommandWin = newwin(COMMAND_WIN_HEIGTH, COMMAND_WIN_WIDTH, 10, COLS/2 - COMMAND_WIN_WIDTH/2);
	box(CommandWin, ' ', 0);

	mvwprintw(CommandWin, 0, 0, "Insert the command:\n");
	mvwprintw(CommandWin, 1, 1, ">_");
	wrefresh(CommandWin);

	strncpy(command, "", 1);
	position = 0;
}

bool CommandUpdate(struct AppState *as) {
	// printf("%s\n", command);

	//  ===== NOT SPECIAL CHARACTERS ==========
	if (as->Input >= 32 && as->Input <= 126) {
		if (position < 255) {
			command[position] = as->Input;
			command[position + 1] = '\0';
			mvwprintw(CommandWin, 1, 2, "%s_", command);
			wrefresh(CommandWin);
			position++;

		} else {
			mvwprintw(stdscr, LINES - 2, 2, "You reached the maximum length!");
			refresh();
		}

		//  ===== BACKSPACE ==========
	} else if (as->Input == 7) {
		if (position > 0) {
			position--;
			command[position] = '\0';
			mvwprintw(CommandWin, 1, 2, "%s_ ", command);
			wrefresh(CommandWin);
		}
	
		// ======= RETURN ============
	} else if (as->Input == '\n') {
		return SwitchState(as, STATE_NORMAL);
	}

	return true;
}

void CommandExit(struct AppState *as) {
	wclear(CommandWin);
	wrefresh(CommandWin);
	delwin(CommandWin);
	refresh();

	// parsing the command
	string8 args[4];
	for (u8 i = 0; i < 4; i++) {
		args[i].str = NULL;
	}

	char *token = strtok(command, " ");
	if (!token) {return;}

	for (u8 i = 0; token; i++) {
		args[i].size = strlen(token);
		args[i].str = (char*) malloc((args[i].size + 1) * sizeof(char));
		strncpy(args[i].str, token, args[i].size + 1);

		token = strtok(NULL, " ");
	}

		// =========MOVE========
	if (strcmp(args[0].str, "move") == 0 || strcmp(args[0].str, "mv") == 0) {
		MoveFile(args[1], args[2]);

		// =========CSV PARSER AND LOADER========
	} else if (strcmp(args[0].str, "ucs-dir") == 0 || strcmp(args[0].str, "ucs") == 0) {
		as->CsvDir.size = strlen(args[1].str);
		as->CsvDir.str = malloc(as->CsvDir.size + 1);
		strncpy(as->CsvDir.str, args[1].str, MIN(as->CsvDir.size + 1, 255));
		ScanCsv(as);

		// =========QUIT========
	} else if (strcmp(args[0].str, "quit") == 0 || strcmp(args[0].str, "q") == 0) {
		exit(0);

		// =========COMMAND NOT EXISTS===========
	} else {
		mvwprintw(stdscr, LINES - 2, 2, "not command %s found\n", args[0].str);
	}

	// free all the args
	for (u8 i = 0; i < 4; i++) {
		if (args[i].str) {
			free(args[i].str);
			args[i].str = NULL;
		}
	}
}
