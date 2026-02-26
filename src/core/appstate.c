#include <malloc.h>
#include <stdlib.h>

#include "appstate.h"
#include "../states/states.h"


bool AppStateInit(struct AppState *as) {
	as->Input = 0;

	as->CsvDir = NULL;
	as->InputDir = NULL;
	as->OutputDir = NULL;

	StateDictInit(&as->States);
	StateInit(&as->CurrState, STATE_COMMAND, as->States);
	as->CurrState->enter(as);

	return true;
}

bool AppStateDeinit(struct AppState *as) {
	as->Input = 0;

	if (as->CsvDir) {
		free(as->CsvDir);
		as->CsvDir = NULL;
	}
	if (as->InputDir) {
		free(as->InputDir);
		as->InputDir = NULL;
	}
	if (as->OutputDir) {
		free(as->OutputDir);
		as->OutputDir = NULL;
	}

	if (as->States) {
		for (u8 i = 0; i < as->States->size; i++) {
			if (as->States->value[i]) {
				free(as->States->value[i]);
				as->States->value[i] = NULL;
			}
		}
		free(as->States);
		as->States = NULL;
	}

	return true;
}
