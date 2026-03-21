#include <stdio.h>
#include <stdlib.h>

#include "move.h"


void MoveFile(string8 from, string8 to) {
	if (!from.str || !to.str) {
		printf("error: the move funciton wants 2 arguments\n");
		return;
	}

	if (rename(from.str, to.str) == 0) {
		printf("%s moved to %s\n", from.str, to.str);
	} else {
		perror("error");
	}
}
