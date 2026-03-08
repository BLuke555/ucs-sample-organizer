#pragma once


enum State {
	NORMAL,
	INSERT
};

struct LinkedListNode {
	char *key;
	char *value;

	struct LinkedListNode *next;
};

struct folderStructNode {
	char *folder;
	char *subFolder;
	char *catID;
	char *description;
	char *keywords;

	struct folderStructNode *next;
};

struct AppState {
	enum State state;
	int input;

	char *csvPath;
	char *inputFolder;
	char *outputFolder;

	struct folderStructNode *folderStruct;
	struct LinkedListNode *files;
};
