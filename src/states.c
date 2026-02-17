#include "states.h"


bool StateInit(struct State **CurrentState, enum StateType InitialState, struct StateDict *States) {
	// initialize memory to current state
	if (!(*CurrentState)) {
		(*CurrentState) = (struct State*) malloc(sizeof(struct State));
	}
	if (!(*CurrentState)) {
		printf("Could not allocate enough memory for the State");
		return false;
	}
	CurrentState = NULL;

	for(i8 i = 0; i < States->size; i++) {
		if (States->key[i] == InitialState) {
			**CurrentState = States->value[i];
		}
	}

	if (*CurrentState == NULL) {
		printf("could not find the state");
		return false;
	}
	
	return true;
}

bool SwitchState(struct AppState *as, enum StateType from, enum StateType to) {

	return true;
}
