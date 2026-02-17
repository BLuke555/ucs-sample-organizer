#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "core.h"
#include "appstate.h"


bool AppInit(struct AppState *as);
bool AppUpdate(struct AppState *as);
void AppDeinit(struct AppState **as);

void GetInput();



int main() {
	struct AppState *appstate = malloc(sizeof(struct AppState));

	if (!appstate) {
		printf("couldn't initialize memory for the appstate.\n");
		return -1;
	}

	// initialize all the memory and the graphics
	if (!AppInit(appstate)) {
		return -1;
	}

	// main loop
	// in which all the calculation si done
	i8 i = 0;
	while (i < 10) {
		GetInput();
		if (!AppUpdate(appstate)) {
			break;		
		}
		i++;
	}

	// deinitialize all the memory and the grapic before colsing it
	AppDeinit(&appstate);

	return 0;
}



bool AppInit(struct AppState *as) {
	printf("intialize\n");
	AppStateInit(as);

	return true;
}

bool AppUpdate(struct AppState *as) {
	printf("main loop\n");

	return true;
}

void AppDeinit(struct AppState **as) {
	printf("deinitializing memory dedicated to appstate\n");
	AppStateDeinit(*as);
	free(*as);
	(*as) = NULL;

	printf("memory deinitialized correctly\n");
}


void GetInput() {
	printf("getting input\n");
}
