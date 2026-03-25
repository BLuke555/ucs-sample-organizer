#pragma once

bool AppInit(struct AppState **as);
void GetInput(struct AppState *as);
bool AppUpdate(struct AppState *as);
void AppDeinit(struct AppState **as);
