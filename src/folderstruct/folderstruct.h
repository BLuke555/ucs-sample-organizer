#include "../core/core.h"


struct LinkedListNode {
	string8 key;
	string16 value;

	struct LinkedListNode *next;
};

struct FolderStructNode {
	string8 Folder;
	string8 SubFolder;
	string8 CatID;
	string16 Description;
	string16 Keywords;

	struct FolderStructNode *next;
};
