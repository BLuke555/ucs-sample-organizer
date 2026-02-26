#include <stdio.h>
#include <string.h>

#include "command.h"
#include "states.h"
#include "../commands/command-funcs.h"

char command[1024];
string8 args[4];



void CommandEnter(struct AppState *as) {
	printf("Insert the command: \n");
	scanf("%[^\n]", command);
}

bool CommandUpdate(struct AppState *as) {
	return SwitchState(as, STATE_NORMAL);
}

void CommandExit(struct AppState *as) {
	char *token = strtok(command, " ");

	if (!token) {return;}

	u8 i = 0;
	while (token) {
		args[i].size = strlen(token);
		args[i].str = (char*) malloc((args[i].size) * sizeof(char));
		strncpy(args[i].str, token, args[i].size + 1);

		token = strtok(NULL, " ");
		i++;
	}

	if (strcmp(args[0].str, "move") == 0 || strcmp(args[0].str, "mv") == 0) {
		move(args);
	}

	for (u8 j = 0; j < 4; j++) {
		free(args[j].str);
		args[j].str = NULL;
	}
}
