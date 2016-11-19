#pragma once

#define DEBUG 1

#define MAX_CHARS_IN_DICTIONARY_WORD 32
#define MAX_LINE MAX_CHARS_IN_DICTIONARY_WORD
#define FIRST_ASCII_CHAR 65

typedef struct TrieNode
{
	// pointers to all of the other nodes
	struct TrieNode *ptrToA;
	struct TrieNode *ptrToB;
	struct TrieNode *ptrToC;
	struct TrieNode *ptrToD;
	struct TrieNode *ptrToE;
	struct TrieNode *ptrToF;
	struct TrieNode *ptrToG;
	struct TrieNode *ptrToH;
	struct TrieNode *ptrToI;
	struct TrieNode *ptrToJ;
	struct TrieNode *ptrToK;
	struct TrieNode *ptrToL;
	struct TrieNode *ptrToM;
	struct TrieNode *ptrToN;
	struct TrieNode *ptrToO;
	struct TrieNode *ptrToP;
	struct TrieNode *ptrToQ;
	struct TrieNode *ptrToR;
	struct TrieNode *ptrToS;
	struct TrieNode *ptrToT;
	struct TrieNode *ptrToU;
	struct TrieNode *ptrToV;
	struct TrieNode *ptrToW;
	struct TrieNode *ptrToX;
	struct TrieNode *ptrToY;
	struct TrieNode *ptrToZ;

	char8_t character;

}TrieNode_t;


typedef struct TrieList
{
	TrieNode_t* characterNode;
	struct TrieList* nextList;

}TrieList_t;


TrieNode_t * createNewTrieNode(char8_t c);

TrieList_t* createNewTrieList(char8_t c);
void pushNewTrieList(TrieList_t * head, char8_t c);
TrieList_t* createInitialTrie();

TrieList_t* parseDictionaryFile(char8_t *filename, int32_t *numWords);

bool validString(char8_t* str);
void AddStringToTrie(TrieList_t* trieList, char8_t* str);