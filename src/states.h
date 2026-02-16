#pragma once

#include "states/normal.h"
#include "states/command.h"

#define MAX_STATES 5

struct State {
	void (*enter)();
	void (*update)();
	void (*exit)();
};


enum StateType {
	NORMAL,
	COMMAND,
};

struct StateDict {
	enum StateType key[MAX_STATES];
	struct State value[MAX_STATES];
};


bool StateInit(struct State **state);
bool SwitchState(enum StateType from, enum StateType to);

void SetStateDict(struct StateDict *dict, enum StateType key, struct State *value);
struct State *GetStateValue(struct StateDict *dict, enum StateType key);
