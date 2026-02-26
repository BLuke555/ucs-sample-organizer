#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "core/core.h"
#include "core/appstate.h"


bool AppInit(struct AppState **as);
bool AppUpdate(struct AppState *as);
void AppDeinit(struct AppState **as);

void GetInput();


int main() {
	struct AppState *appstate =(struct AppState*) malloc(sizeof(struct AppState));
	printf("%lu\n", sizeof(struct AppState));
	bool running;

	if (!AppInit(&appstate)) {
		return -1;
	}

	do {
		GetInput();
		running = AppUpdate(appstate);
	} while (running);

	AppDeinit(&appstate);

	return 0;
}


bool AppInit(struct AppState **as) {
	(*as) = (struct AppState*) malloc(sizeof(struct AppState));
	AppStateInit(*as);

	return true;
}

bool AppUpdate(struct AppState *as) {
	return as->CurrState->update(as);
}

void AppDeinit(struct AppState **as) {
	AppStateDeinit(*as);
	free(*as);
	(*as) = NULL;

	printf("memory deinitialized correctly\n");
}


void GetInput() {
	printf("getting input\n");
}
