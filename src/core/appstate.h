#pragma once


#include <string.h>

#include "core.h"
#include "../states/states.h"
#include "../folderstruct/folderstruct.h"


struct AppState {
	char Input;

	string8 CsvDir;
	string8 InputDir;
	string8 OutputDir;

	struct State *CurrState;
	struct StateDict *States;

	struct FolderStructNode *FolderStruct;
	struct LinkedListNode *Files;
};

bool AppStateInit(struct AppState **as);
bool AppStateDeinit(struct AppState *as);
