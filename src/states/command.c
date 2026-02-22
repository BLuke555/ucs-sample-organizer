#include <stdio.h>

#include "command.h"
#include "../states.h"


void CommandEnter(struct AppState *as) {
	printf("Insert the command: ");
}

void CommandUpdate(struct AppState *as) {
	// SwitchState(as, enum StateType from, enum StateType to)
	printf("command update function");
}

void CommandExit(struct AppState *as) {

}
