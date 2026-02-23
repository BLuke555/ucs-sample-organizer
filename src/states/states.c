#include <stdbool.h>
#include <stdio.h>

#include "states.h"
#include "../core/appstate.h"



bool StateDictInit(struct StateDict **Dictionary) {
	(*Dictionary) = (struct StateDict*) malloc(sizeof(struct StateDict));

	(*Dictionary)->size = 2;

	// Set States
	// NORMAL MODE
	struct State *StateNormal = (struct State*) malloc(sizeof(struct State*));

	StateNormal->enter = &NormalEnter;
	StateNormal->update = &NormalUpdate;
	StateNormal->exit = &NormalExit;

	(*Dictionary)->key[0] = STATE_NORMAL;
	(*Dictionary)->value[0] = StateNormal;

	// COMMAND MODE
	struct State *StateCommand = (struct State*) malloc(sizeof(struct State*));

	StateCommand->enter = &CommandEnter;
	StateCommand->update = &CommandUpdate;
	StateCommand->exit = &CommandExit;

	(*Dictionary)->key[1] = STATE_COMMAND;
	(*Dictionary)->value[1] = StateCommand;

	return true;
}


bool StateInit(struct State **CurrentState, enum StateType InitialState, struct StateDict *States) {
	// initialize memory to current state
	if (!(*CurrentState)) {
		(*CurrentState) = (struct State*) malloc(sizeof(struct State));
	}
	if (!(*CurrentState)) {
		printf("Could not allocate enough memory for the State");
		return false;
	}
	*CurrentState = NULL;

	for(i8 i = 0; i < States->size; i++) {
		if (States->key[i] == InitialState) {
			*CurrentState = States->value[i];
		}
	}

	if (!*CurrentState) {
		printf("could not find the state");
		return false;
	}

 return true;
}


bool SwitchState(struct AppState *as, enum StateType ToState) {
	enum StateType FromState;
	as->CurrState->exit(as);

	for (u8 i = 0; i < as->States->size; i++) {
		if (as->States->key[i] == ToState) {
			as->CurrState = as->States->value[i];
			break;
		}
	} 

	as->CurrState->enter(as);

	return true;
}
