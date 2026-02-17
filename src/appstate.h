#pragma once

#include <stdbool.h>

#include "states.h"


struct AppState {
	char Input;

	char *CsvDir;
	char *InputDir;
	char *OutputDir;

	struct State *CurrState;
	struct StateDict *States;
};

bool AppStateInit(struct AppState *as);
bool AppStateDeinit(struct AppState *as);
