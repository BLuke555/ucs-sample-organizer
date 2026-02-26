#include <stdio.h>
#include <stdlib.h>

#include "move.h"


void move(string8 args[4]) {
	if (!args[1].str || !args[2].str) {
		printf("error: the move funciton wants 2 arguments");
		return;
	}

	if (rename(args[1].str, args[2].str) == 0) {
		printf("%s moved to %s\n", args[1].str, args[2].str);
	} else {
		perror("error");
	}
}
