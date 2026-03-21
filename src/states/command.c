#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../core/appstate.h"
#include "command.h"
#include "states.h"
#include "../commands/command-funcs.h"

char command[256];


void CommandEnter(struct AppState *as) {
	strncpy(command, "", 1);

	printf("Insert the command: \n");
}

bool CommandUpdate(struct AppState *as) {
	// printf("%s\n", command);

	if (as->Input == '\n') {
		mvprintw(2, 0, "hello");
		// return SwitchState(as, STATE_NORMAL);
	}

	return true;
}

void CommandExit(struct AppState *as) {
	// parsing the command
	string8 args[4];
	for (u8 j = 0; j < 4; j++) {
		args[j].str = NULL;
	}

	char *token = strtok(command, " ");
	if (!token) {return;}

	u8 i = 0;
	while (token) {
		args[i].size = strlen(token);
		args[i].str = (char*) malloc((args[i].size + 1) * sizeof(char));
		strncpy(args[i].str, token, args[i].size + 1);

		token = strtok(NULL, " ");
		i++;
	}


		// =========MOVE========
	if (strcmp(args[0].str, "move") == 0 || strcmp(args[0].str, "mv") == 0) {
		MoveFile(args[1], args[2]);

		// =========CSV PARSER AND LOADER========
	} else if (strcmp(args[0].str, "csv") == 0) {
		as->CsvDir.size = strlen(args[1].str);
		as->CsvDir.str = malloc(as->CsvDir.size + 1);
		strncpy(as->CsvDir.str, args[1].str, min(as->CsvDir.size + 1, 255));
		ScanCsv(as);

		// =========QUIT========
	} else if (strcmp(args[0].str, "quit") == 0 || strcmp(args[0].str, "q") == 0) {
		exit(0);

		// =========COMMAND NOT EXISTS===========
	} else {
		printf("not command %s found\n", args[0].str);
	}

	for (u8 j = 0; j < 4; j++) {
		if (args[j].str) {
			free(args[j].str);
			args[j].str = NULL;
		}
	}
}
