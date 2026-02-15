#include "states.h"

struct AppState {
	int Input;

	char *CsvDir;
	char *InputDir;
	char *OutputDir;

	enum State state;
};


bool AppStateInit(struct AppState *as);
bool AppStateDeinit(struct AppState *as);
