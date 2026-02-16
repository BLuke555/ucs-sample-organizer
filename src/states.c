#include "states.h"


bool StateInit(struct State **state) {
	(*state) = malloc(sizeof(struct State));
}

bool SwitchState(enum StateType from, enum StateType to) {
	return true;
}
