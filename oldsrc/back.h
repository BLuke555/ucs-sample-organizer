#pragma once

#include "core.h"


void insertPath(struct AppState *as, char **path, char *message);
bool scanCsv(struct AppState *as, FILE *pFile);
bool scanDir(struct AppState *as, char *path, struct LinkedListNode **file, DIR *pDir);
