#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "../core/core.h"
#include "normal.h"
#include "command.h"

#define MAX_STATES 5

struct AppState;

struct State {
	void (*enter)(struct AppState*);
	bool (*update)(struct AppState*);
	void (*exit)(struct AppState*);
};

enum StateType {
	STATE_NORMAL,
	STATE_COMMAND,
};

struct StateDict {
	i8 size;
	enum StateType key[MAX_STATES];
	struct State *value[MAX_STATES];
};


bool StateDictInit(struct StateDict **Dictionary);
bool StateInit(struct State **CurrentState, enum StateType InitialState, struct StateDict *States);
bool SwitchState(struct AppState *as, enum StateType to);

