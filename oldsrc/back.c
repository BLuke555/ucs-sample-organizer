#include <dirent.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "core.h"
#include "tui.h"
#include "back.h"

#define SCAN_BUFFER_SIZE 4096



void insertPath(struct AppState *as, char **path, char *message) {
	bool stillWriting = true;
	tuiInsertString(as, message);

	char buff[256];
	int i = 0;

	do {
		as->input = getch();
		tuiWrite(as);

		if (as->input != ERR && as->input >= 33 && as->input <= 126 && i < 255) {
			buff[i] = as->input;
			i++;
			buff[i] = '\0';

		} else if (as->input == '\b') {
			i--;

		} else if (as->input == '\n') {
			stillWriting = false;

		} else if (as->input != ERR && i == 255) {
			tuiLog("Max string size reached\n");
			as->input = '\b';
			tuiWrite(as);
		}

	} while (stillWriting);

	// save the path
	*path = malloc((strlen(buff) + 1) * sizeof(buff[0]));
	strcpy(*path, buff);
}


bool scanCsv(struct AppState *as, FILE *pFile) {
	char countBuff[1];
	char buff[SCAN_BUFFER_SIZE];
	// int row = 0;
	struct folderStructNode **node = &as->folderStruct;
	(*node) = (struct folderStructNode *) malloc(sizeof(struct folderStructNode));

	// get the rows
	while (fgets(buff, SCAN_BUFFER_SIZE, pFile)) {
		if (buff[strlen(buff) - 1] == '\n') {
			buff[strlen(buff) - 1] = '\0';
		}

		char *token = strtok(buff, ",");
		char temp[SCAN_BUFFER_SIZE];
		bool isInsideQuotes = false;
		int column = 0;


		// get the column
		while (token) {
			// if commas are inside double quotes you have to glue what
			// would be counted as different column
			if (isInsideQuotes) {
				strcat(temp, ",");
				strcat(temp, token);
				// check if the double quotes are closed
				if (temp[strlen(temp) - 1] == '"') {
					isInsideQuotes = false;
				}
			} else {
				// check if it needs to glue inside a single column
				strcpy(temp, token);
				if (temp[0] == '"') {
					isInsideQuotes = true;
				}
			}

			// check if the code is finished scanning a column
			if (!isInsideQuotes) {
				//clean up the string
				if (temp[0] == '"') {
					for (int i = 0; i < strlen(temp); i++) {
						temp[i] = temp[i + 1];
					}
				}
				if (temp[strlen(temp) - 1] == '"') {
					temp[strlen(temp) - 1] = '\0';
				}

				// save each column inside the correct array based on the correct array
				switch (column) {
					case 0:
						// folder
						(*node)->folder = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						if (!(*node)->folder) {
							tuiLog("couldn't allocate that much memory");
							getch();
							return false;
						}
						strcpy((*node)->folder, temp);
						break;
					case 1:
						// subfolder
						(*node)->subFolder = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						if (!(*node)->subFolder) {
							tuiLog("couldn't allocate that much memory");
							getch();
							return false;
						}
						strcpy((*node)->subFolder, temp);
						break;
					case 2:
						// catid
						(*node)->catID = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						if (!(*node)->catID) {
							tuiLog("couldn't allocate that much memory");
							getch();
							return false;
						}
						strcpy((*node)->catID, temp);
						break;
					case 4:
						//description 
						(*node)->description = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						if (!(*node)->description) {
							tuiLog("couldn't allocate that much memory");
							getch();
							return false;
						}
						strcpy((*node)->description, temp);
						break;
					case 5:
						// keywords
						(*node)->keywords = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						if (!(*node)->keywords) {
							tuiLog("couldn't allocate that much memory");
							getch();
							return false;
						}
						strcpy((*node)->keywords, temp);
						break;
				}
				column++;
			}
			token = strtok(NULL, ",");
		}
		node = &(*node)->next;
		*node = (struct folderStructNode*)malloc(sizeof(struct folderStructNode));
		// row++;
	}

	free(*node);
	(*node) = NULL;

	return true;
}


bool scanDir(struct AppState *as, char *path, struct LinkedListNode **file, DIR *pDir) {
	struct dirent *pEntry;

	while (pEntry = readdir(pDir)) {
		tuiLog(pEntry->d_name);
		getch();
	}

	return true;
}
