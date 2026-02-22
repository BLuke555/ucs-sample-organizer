#include <malloc.h>
#include <stdlib.h>

#include "appstate.h"
#include "states.h"


bool AppStateInit(struct AppState *as) {
	as->Input = 0;

	as->CsvDir = NULL;
	as->InputDir = NULL;
	as->OutputDir = NULL;

	StateDictInit(&as->States);
	StateInit(&as->CurrState, STATE_COMMAND, as->States);
	return true;
}

bool AppStateDeinit(struct AppState *as) {
	as->Input = 0;

	free(as->CsvDir);
	as->CsvDir = NULL;
	free(as->InputDir);
	as->InputDir = NULL;
	free(as->OutputDir);
	as->OutputDir = NULL;

	return true;
}
