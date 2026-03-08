#include <malloc.h>
#include <stdlib.h>

#include "appstate.h"
#include "../states/states.h"


bool AppStateInit(struct AppState **as) {
	(*as) = (struct AppState*) malloc(sizeof(struct AppState));
	if (!*as) {
		printf("Couldn't allocate memory for the appstate");
		return false;
	}

	(*as)->Input = 0;

	(*as)->CsvDir.size = 0;
	(*as)->CsvDir.str = NULL;
	(*as)->InputDir.size = 0;
	(*as)->InputDir.str = NULL;
	(*as)->OutputDir.size = 0;
	(*as)->OutputDir.str = NULL;

	StateDictInit(&(*as)->States);
	StateInit(&(*as)->CurrState, STATE_COMMAND, (*as)->States);
	(*as)->CurrState->enter(*as);

	return true;
}

bool AppStateDeinit(struct AppState *as) {
	as->Input = 0;

	if (as->CsvDir.str) {
		as->CsvDir.size = 0;
		free(as->CsvDir.str);
		as->CsvDir.str = NULL;
	}
	if (as->InputDir.str) {
		as->InputDir.size = 0;
		free(as->InputDir.str);
		as->InputDir.str = NULL;
	}
	if (as->OutputDir.str) {
		as->OutputDir.size = 0;
		free(as->OutputDir.str);
		as->OutputDir.str = NULL;
	}
	StateDictDeinit(&as->States);

	return true;
}
