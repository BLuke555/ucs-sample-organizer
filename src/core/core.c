#include <string.h>

#include "core.h"



bool EndsWith(const char* str, const char* suffix) {
	return strncmp(str + strlen(str) - strlen(suffix), suffix, strlen(suffix)) == 0;
}

bool StartsWith(const char* str, const char* prefix) {
	return strncmp(str, prefix, strlen(prefix)) == 0;
}
