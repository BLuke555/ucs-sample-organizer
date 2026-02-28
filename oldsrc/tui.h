#pragma once

#include "core.h"


void tuiLog(char *log);
bool tuiInit();
void tuiWrite(struct AppState *as);
void tuiInsertString(struct AppState *as, char *string);
bool tuiUpdate(struct AppState *as);
bool tuiDeinit();
