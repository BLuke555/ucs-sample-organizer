#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <curses.h>

#include "core.h"
#include "back.h"
#include "tui.h"


bool appInit(struct AppState *as);
bool appUpdate(struct AppState *as);
void appDeinit(struct AppState *as);


int main() {
	struct AppState appstate;
	bool running;

	//initialize the app
	if (!appInit(&appstate)) {
		printf("Couldn't initialize the app\n");
		return -1;
	}

	// main loop
	do {
		// get inputs and then process those inputs
		appstate.input = getch();
		running = appUpdate(&appstate);
	} while (running);

	// deinitialize the app by freeing all the memory
	// before it closes
	appDeinit(&appstate);

	return 0;
}


bool appInit(struct AppState *as) {
	// initialize all the AppState strings by make sure don't 
	// have random values or point to who knows where
	as->csvPath = NULL;
	as->inputFolder = NULL;
	as->outputFolder = NULL;

	as->folderStruct = NULL;
	as->files = NULL;

	
	// MOMENATRLY SET THE csvPath
	as->csvPath = malloc(sizeof("./data/ucs.csv"));
	strcpy(as->csvPath, "./data/ucs.csv");

	//initialize the TUI
	tuiInit();

	// scan csv for ucs folder structure
	bool scanning;
	do {
		if (as->csvPath == NULL) {
			insertPath(as, &as->csvPath, "Insert the path to the csv containing the folder struct:");
		}

		// if csvPath is still NULL get error and crash
		if (as->csvPath == NULL) {
			perror("Couldn't store the path");
			return false;
		}

		// getting infos on the folder struct by scanning the given csv
		FILE *pCsv = fopen(as->csvPath, "r");

		if (!pCsv) {
			tuiLog("csv selected not valid, insert a valid path please");
			scanning = true;

			free(as->csvPath);
			as->csvPath = NULL;
		} else {
			printf("csv loaded\n");
			if (!scanCsv(as, pCsv)) {
				getch();
				fclose(pCsv);

				return false;
			} else {
				scanning = false;
			}
			fclose(pCsv);
			printf("csv closed");
		}
	}while (scanning);

	free(as->csvPath);
	as->csvPath = NULL;

	struct folderStructNode **node = &as->folderStruct;
	while (node) {
		printf("%s, %s, %s, %s, %s\n", (*node)->folder, (*node)->subFolder, (*node)->catID, (*node)->description, (*node)->keywords);
		node = &(*node)->next;
	}

	return true;

	// get an input folder
	do {
		if (!as->inputFolder) {
			insertPath(as, &as->inputFolder, "Insert the path to the folder you want to organize");
		}

		// if it couldn't store the path crash
		if (as->inputFolder == NULL) {
			perror("Couldn't store the path");
			return false;
		}
		
		// try to open the directory to see if it exist
		DIR *pDir = opendir(as->inputFolder);

		if (!pDir) {
			tuiLog("Couldn't open the path you choose, this path may not exist or I cannot have access to it, pls select a new path");
			scanning = true;

			free(as->inputFolder);
			as->inputFolder = NULL;
		} else {
			// check if the scan was a mess
			if (!scanDir(as, as->inputFolder, &as->files, pDir)) {
				getch();
				return false;
			} else {
				// exit the function
				scanning = false;
			}
		}

	} while(scanning);

	return true;
}


bool appUpdate(struct AppState *as) {
	tuiLog("press any key to close the application");
	getch();

	// Sleep(100);
	return false;
}


void appDeinit(struct AppState *as) {
	// free all the memory
	void freeArray(char ***array) {
		printf("size of array: %d\n", sizeof(*array) / sizeof(*array[0]));
		for (int i = 0; i < (sizeof(*array) / sizeof(*array[0])); i++) { 
			if (*array[i]) {
				printf("%s\n", *array[i]);
				free(*array[i]);
				array[i] = NULL;
			}
		}
		printf("array's elements deinitialized");

		if (array) {
			free(*array);
		}
		printf("array deinitialized");
	}

	as->input = 0;
	printf("input deinitialized\n");

	if (as->csvPath) {
		free(as->csvPath);
		as->csvPath = NULL;
	}
	printf("csv path deinitialized\n");
	if (as->inputFolder) {
		free(as->inputFolder);
		as->inputFolder = NULL;
	}
	printf("input folder deinitialized\n");
	if (as->outputFolder) {
		free(as->outputFolder);
		as->outputFolder = NULL;
	}
	printf("output folder deinitialized\n");

	if (as->folderStruct) {
		free(as->folderStruct);
		as->folderStruct = NULL;
	}
	printf("folder structure deinitialized");
	if (as->files) {
		free(as->files);
		as->files = NULL;
	}
	printf("files deinitialized\n");

	printf("all the memory got correctly cleaned");

	tuiDeinit();
}
