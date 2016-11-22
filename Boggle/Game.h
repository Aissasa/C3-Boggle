#pragma once
#ifdef GAME_CPP
#define extern 
#endif

#define DEBUG 0

typedef struct wordList
{
	char8_t *word;
	TrieNode_t* sourceNode;       // added to make resetting the game faster
	struct wordList *nextWordNode;
}wordListT;

extern wordListT *topOfWordList;

wordListT * createWord(char8_t * word, TrieNode_t* sourceNode);
void addWordToEndList(wordListT** list, char8_t * word, TrieNode_t* sourceNode);

void initGame(char8_t ** board);
void buildRandomBoard(char8_t ** board);
int32_t rangedRandom(int32_t min, int32_t max);
void searchForWords(char8_t ** board, TrieList_t* trie);
void printBoard(char8_t ** board);
void printWords();
void resetGame();

void initBoard(char8_t ** board);
char8_t getRandomCharacterFromDie(const char8_t* die);
void navigateBoard(TrieNode_t* characterNode, char8_t ** board, uchar8_t row, uchar8_t col, char8_t* currentWord, uchar8_t** pathTaken);

extern const char8_t* Dice[];

#undef extern