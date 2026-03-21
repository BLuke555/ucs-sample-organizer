#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "csv.h"

#define SCAN_BUFFER_SIZE 4096


bool ScanCsv(struct AppState *as) {
	FILE *pCsv = fopen(as->CsvDir.str, "r");

	if (!pCsv) {
		printf("file not found");
		return false;
	}

	char buff[SCAN_BUFFER_SIZE];
	struct FolderStructNode **node = &as->FolderStruct;
	(*node) = (struct FolderStructNode *) malloc(sizeof(struct FolderStructNode));

	// get the rows
	while (fgets(buff, SCAN_BUFFER_SIZE, pCsv)) {
		if (buff[strlen(buff) - 1] == '\n') {
			buff[strlen(buff) - 1] = '\0';
		}

		char *token = strtok(buff, ",");
		char temp[SCAN_BUFFER_SIZE];
		bool isInsideQuotes = false;
		u8 column = 0;

		while (token) {
			if (isInsideQuotes) {
				strcat(temp, ",");
				strcat(temp, token);
				// exit quote
				if (temp[strlen(temp) - 1] == '"') {
					isInsideQuotes = false;
				}
			} else {
				strcpy(temp, token);
				// enter quotes
				if (temp[0] == '"') {
					isInsideQuotes = true;
				}
			}


			if (!isInsideQuotes) {
				//clean up the string
				if (temp[0] == '"') {
					for (u8 i = 0; i < strlen(temp); i++) {
						temp[i] = temp[i + 1];
					}
				}
				if (temp[strlen(temp) - 1] == '"') {
					temp[strlen(temp) - 1] = '\0';
				}

				switch (column) {
					case 0:
						// =======FOLDER=======
						(*node)->Folder.size = strlen(temp);
						(*node)->Folder.str = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						strncpy((*node)->Folder.str, temp, (*node)->Folder.size + 1);
						break;
					case 1:
						// =======SUBFOLDER=======
						(*node)->SubFolder.size = strlen(temp);
						(*node)->SubFolder.str = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						strncpy((*node)->SubFolder.str, temp, (*node)->SubFolder.size + 1);
						break;
					case 2:
						// =======CATID=======
						(*node)->CatID.size = strlen(temp);
						(*node)->CatID.str = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						strncpy((*node)->CatID.str, temp, (*node)->CatID.size + 1);
						break;
					case 4:
						// =======DESCRIPTION=======
						(*node)->Description.size = strlen(temp);
						(*node)->Description.str = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						strncpy((*node)->Description.str, temp, (*node)->Description.size + 1);
						break;
					case 5:
						// =======KEYWORDS=======
						(*node)->Keywords.size = strlen(temp);
						(*node)->Keywords.str = (char *) malloc((strlen(temp) + 1) * sizeof(char));
						strncpy((*node)->Keywords.str, temp, (*node)->Keywords.size + 1);
						break;
				}
				column++;
			}
			token = strtok(NULL, ",");
		}

		node = &(*node)->next;
		*node = (struct FolderStructNode*)malloc(sizeof(struct FolderStructNode));

		if (!(*node)) exit(-1);
	}

	// free the last pending node
	free(*node);
	(*node) = NULL;

	fclose(pCsv);

	return true;
}
