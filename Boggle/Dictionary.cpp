#define DICTIONARY_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "types.h"
#include "Dictionary.h"
// note deleted some headers here

TrieNode_t * createNewTrieNode(char8_t c)
{
	TrieNode_t* node = (TrieNode_t*)malloc(sizeof(TrieNode_t));

	node->character = c;

	node->ptrToA = nullptr;
	node->ptrToB = nullptr;
	node->ptrToC = nullptr;
	node->ptrToD = nullptr;
	node->ptrToE = nullptr;
	node->ptrToF = nullptr;
	node->ptrToG = nullptr;
	node->ptrToH = nullptr;
	node->ptrToI = nullptr;
	node->ptrToJ = nullptr;
	node->ptrToK = nullptr;
	node->ptrToL = nullptr;
	node->ptrToM = nullptr;
	node->ptrToN = nullptr;
	node->ptrToO = nullptr;
	node->ptrToP = nullptr;
	node->ptrToQ = nullptr;
	node->ptrToR = nullptr;
	node->ptrToS = nullptr;
	node->ptrToT = nullptr;
	node->ptrToU = nullptr;
	node->ptrToV = nullptr;
	node->ptrToW = nullptr;
	node->ptrToX = nullptr;
	node->ptrToY = nullptr;
	node->ptrToZ = nullptr;

	return node;
}

TrieList_t* createNewTrieList(char8_t c)
{
	TrieList_t* list = (TrieList_t*)malloc(sizeof(TrieList_t));

	list->characterNode = createNewTrieNode(c);
	list->nextList = nullptr;

	return list;

}

void pushNewTrieList(TrieList_t ** head, char8_t c)
{
	if (*head == nullptr)
	{
		*head = createNewTrieList(c);
	}
	else
	{
		TrieList_t* current = *head;

		while (current->nextList != nullptr)
		{
			current = current->nextList;
		}

		current->nextList = createNewTrieList(c);
	}
}

TrieList_t* createInitialTrie()
{
	TrieList_t* head = nullptr;

	for (char8_t currentChar = 'A'; currentChar <= 'Z'; currentChar++)
	{
		pushNewTrieList(&head, currentChar);
	}

	return head;
}


TrieList_t* parseDictionaryFile(char8_t *filename, int32_t *numWords)
{
	TrieList_t* trieList = createInitialTrie();

	FILE* dictionaryFile = fopen(filename, "r");

	char8_t currentString[MAX_CHARS_IN_DICTIONARY_WORD];

	while (fscanf(dictionaryFile, "%s", currentString) == 1)
	{
		if (!validString(currentString))
		{
			continue;
		}

		*numWords++;

		// todo process the string and add it to the trie
		AddStringToTrie(trieList, currentString);

		if (feof(dictionaryFile))
		{
			break;
		}
	}

	fclose(dictionaryFile);

	return trieList;
}

bool validString(char8_t* str)
{
	bool valid = true;
	int32_t length = strlen(str);

	if (length < 4)
	{
		valid = false;
	}
	else
	{
		for (char8_t i = 0; i < length; i++)
		{
			// make sure it's upper case
			char8_t c = toupper(str[i]);
			if (c<'A' || c>'Z')
			{
				valid = false;
			}
		}
	}
	return valid;
}

void AddStringToTrie(TrieList_t* trieList, char8_t* str)
{
	// get to the needed node in the trie list
	char8_t c = toupper(str[0]);

	TrieList_t* currentList = trieList;
	while (currentList != nullptr)
	{
		if (c == currentList->characterNode->character)
		{
			break;
		}

		currentList = currentList->nextList;
	}
#if DEBUG
	if (currentList == nullptr)
	{
		printf("Reached end of list, something is wrong");
	}
#endif // DEBUG

	TrieNode_t* currentNode = currentList->characterNode;

	int32_t length = strlen(str);
	for (uchar8_t i = 1; i < length; i++)
	{
		c = toupper(str[i]);
		TrieNode_t** charNodePointer = &(currentNode->ptrToA) + (c - FIRST_ASCII_CHAR) /** sizeof(TrieNode_t*)*/;
		if (*charNodePointer == nullptr)
		{
			*charNodePointer = createNewTrieNode(c);
		}
		currentNode = *(charNodePointer);
	}

#if DEBUG
	//currentNode = currentList->characterNode;

#endif // DEBUG
}



