
#include <malloc.h>
#include <ncurses.h>
#include <string.h>

#include "core/appstate.h"


bool AppInit(struct AppState **as);
void GetInput(struct AppState *as);
bool AppUpdate(struct AppState *as);
void AppDeinit(struct AppState **as);


int main(int argc, char **argv) {
	struct AppState *appstate;

	if (!AppInit(&appstate)) return -1;

	if (argc > 0) {
		appstate->InputDir.size = strlen(argv[1]);
		appstate->InputDir.str = (char*) malloc(appstate->InputDir.size);
		strncpy(appstate->InputDir.str, argv[1], appstate->InputDir.size);
	}

	do {
		GetInput(appstate);
	} while (AppUpdate(appstate));

	AppDeinit(&appstate);

	return 0;
}


bool AppInit(struct AppState **as) {
	initscr();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	noecho();
	refresh();

	return AppStateInit(as);
}


void GetInput(struct AppState *as) {
	as->Input = wgetch(stdscr);

	if (as->Input != 255) {
		mvprintw(1, 0, "input: %d\n", as->Input);
	}
}

bool AppUpdate(struct AppState *as) {
	return as->CurrState->update(as);
}

void AppDeinit(struct AppState **as) {
	AppStateDeinit(*as);
	free(*as);
	(*as) = NULL;
}
