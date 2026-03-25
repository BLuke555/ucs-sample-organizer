#pragma once

#include <ncurses.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "typedefine.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

bool EndsWith(const char* str, const char* suffix);
bool StartsWith(const char* str, const char* prefix);
