#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "core/core.h"
#include "core/appstate.h"

// #define getch() wgetch(stdscr)


bool AppInit(struct AppState **as);
void GetInput(struct AppState *as);
bool AppUpdate(struct AppState *as);
void AppDeinit(struct AppState **as);


int main() {
	struct AppState *appstate;

	if (!AppInit(&appstate)) return -1;

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

	return AppStateInit(as);
}


void GetInput(struct AppState *as) {
	as->Input = wgetch(stdscr);

	if (as->Input != 255) {
		mvprintw(1, 0,
				"input: %d\n", as->Input);
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
