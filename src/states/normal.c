#include "states.h"
#include "normal.h"
#include "../core/appstate.h"
#include <stdbool.h>

void NormalEnter(struct AppState *as) {
	printf("Normal enter function\n");
}

bool NormalUpdate(struct AppState *as) {
	if (as->Input == ':') {
		return SwitchState(as, STATE_COMMAND);
	}

	return true;
}

void NormalExit(struct AppState *as) {
	
}
