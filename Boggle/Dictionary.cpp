#define DICTIONARY_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "types.h"
#include "Dictionary.h"

// creates a new trie node
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

	node->endOfWord = false;
	node->isFound = false;

	return node;
}

// returns a pointer to the node corresponding the wanted character
TrieNode_t * getTrieNodeByChar(TrieNode_t* charNode, char8_t c)
{
	TrieNode_t** charNodePointer = &(charNode->ptrToA) + (c - FIRST_ASCII_CHAR);

	return *charNodePointer;
}

// creates a new head node for a trie
TrieList_t* createNewTrieList(char8_t c)
{
	TrieList_t* list = (TrieList_t*)malloc(sizeof(TrieList_t));

	list->characterNode = createNewTrieNode(c);
	list->nextList = nullptr;

	return list;
}

// adds a new head node to the tries list
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

// gets the pointer to the head node in the trie list corresponding to the wanted character
TrieList_t * getTrieListByChar(TrieList_t * head, char8_t c)
{
	TrieList_t* currentList = head;
	while (currentList != nullptr)
	{
		if (currentList->characterNode->character == c)
		{
			break;
		}

		currentList = currentList->nextList;
	}

	assert(currentList != nullptr);

	return currentList;
}

// create an initial empty tries list
TrieList_t* createInitialTrie()
{
	TrieList_t* head = nullptr;

	for (char8_t currentChar = 'A'; currentChar <= 'Z'; currentChar++)
	{
		pushNewTrieList(&head, currentChar);
	}

	return head;
}

// reads a file and builds tries from it that represent the dictionary
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

		(*numWords)++;

		// processes the string and adds it to the trie
		AddStringToTrie(trieList, currentString);

		if (feof(dictionaryFile))
		{
			break;
		}
	}

	fclose(dictionaryFile);

	return trieList;
}

// checks if a string is valid to be added to the tries
bool validString(char8_t* str)
{
	bool valid = true;
	int32_t length = strlen(str);

	if (length < MIN_ACCEPTABLE_WORD_LENGTH)
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

// adds a string to a trie
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

	assert(currentList != nullptr);

	TrieNode_t* currentNode = currentList->characterNode;

	int32_t length = strlen(str);
	for (uchar8_t i = 1; i < length; i++)
	{
		c = toupper(str[i]);

		TrieNode_t** charNodePointer = &(currentNode->ptrToA) + (c - FIRST_ASCII_CHAR) ;
		if (*charNodePointer == nullptr)
		{
			*charNodePointer = createNewTrieNode(c);
		}

		// if it's the last character
		if (i == length - 1)
		{
			(*charNodePointer)->endOfWord = true;
		}

		currentNode = *(charNodePointer);
	}
}



