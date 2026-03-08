#pragma once

#include <stdbool.h>

#include "../states/states.h"


struct AppState {
	char Input;

	string8 CsvDir;
	string8 InputDir;
	string8 OutputDir;

	struct State *CurrState;
	struct StateDict *States;
};

bool AppStateInit(struct AppState **as);
bool AppStateDeinit(struct AppState *as);
