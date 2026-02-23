#include <stdio.h>

#include "command.h"
#include "states.h"


void CommandEnter(struct AppState *as) {
	printf("Insert the command: ...\n");
}

void CommandUpdate(struct AppState *as) {
	printf("command update function\n");
	SwitchState(as, STATE_NORMAL);
}

void CommandExit(struct AppState *as) {

}
