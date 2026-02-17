#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "core.h"
#include "appstate.h"
#include "states/normal.h"
#include "states/command.h"

#define MAX_STATES 5

struct State {
	void (*enter)();
	void (*update)();
	void (*exit)();
};


enum StateType {
	STATE_NORMAL,
	STATE_COMMAND,
};

struct StateDict {
	i8 size;
	enum StateType key[MAX_STATES];
	struct State value[MAX_STATES];
};


bool StateInit(struct State **CurrentState, enum StateType InitialState, struct StateDict *States);
bool SwitchState(struct AppState *as, enum StateType from, enum StateType to);

void SetStateDict(struct StateDict *dict, enum StateType key, struct State *value);
struct State *GetStateValue(struct StateDict *dict, enum StateType key);
