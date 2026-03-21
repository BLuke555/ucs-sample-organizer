#include "normal.h"
#include "states.h"

void NormalEnter(struct AppState *as) {
	printf("Normal enter function\n");
}

bool NormalUpdate(struct AppState *as) {
	return SwitchState(as, STATE_COMMAND);
}

void NormalExit(struct AppState *as) {
	
}
