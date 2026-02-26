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
	SwitchState(as, STATE_NORMAL);

	return true;
}


void CommandExit(struct AppState *as) {
	u8 i = 0;
	char *token = strtok(command, " ");

	while (token) {
		args[i].size = strlen(token);
		args[i].str = (char*) malloc((args[i].size + 1) * sizeof(char));
		strncpy(args[i].str, token, args[i].size);

		token = strtok(NULL, " ");
		i++;
	}

	printf("%s\n", args[0].str);
	if (strcmp(args[0].str, "move") == 0) {
		printf("daje");
		move(args);
	}

	printf("done\n");
}
