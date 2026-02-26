#pragma  once

#include <stdbool.h>

struct AppState;

void NormalEnter(struct AppState *as);
bool NormalUpdate(struct AppState *as);
void NormalExit(struct AppState *as);
