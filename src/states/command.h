#pragma  once

#include <stdbool.h>

struct AppState;

void CommandEnter(struct AppState *as);
bool CommandUpdate(struct AppState *as);
void CommandExit(struct AppState *as);
