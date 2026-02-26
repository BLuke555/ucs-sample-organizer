#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "states.h"
#include "../core/appstate.h"



bool StateDictInit(struct StateDict **Dictionary) {
	(*Dictionary) = (struct StateDict*) malloc(sizeof(struct StateDict));

	(*Dictionary)->size = 2;
	for (u8 i = 0; i < (*Dictionary)->size; i++) {
		(*Dictionary)->value[i] = NULL;
	}

	// Set States
	// NORMAL MODE
	(*Dictionary)->key[0] = STATE_NORMAL;
	(*Dictionary)->value[0] = (struct State*) malloc(sizeof(struct State));

	(*Dictionary)->value[0]->enter = &NormalEnter;
	(*Dictionary)->value[0]->update = &NormalUpdate;
	(*Dictionary)->value[0]->exit = &NormalExit;


	// COMMAND MODE
	(*Dictionary)->key[1] = STATE_COMMAND;
	(*Dictionary)->value[1] = (struct State*) malloc(sizeof(struct State));

	(*Dictionary)->value[1]->enter = &CommandEnter;
	(*Dictionary)->value[1]->update = &CommandUpdate;
	(*Dictionary)->value[1]->exit = &CommandExit;

	return true;
}


bool StateInit(struct State **CurrentState, enum StateType InitialState, struct StateDict *States) {
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
