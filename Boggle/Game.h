#pragma once
#ifdef GAME_CPP
#define extern 
#endif


typedef struct wordList
{
	char8_t *word;
	struct wordList *nextWord;
}wordListT;

extern wordListT *topOfWordList;

void initGame(char8_t ** board);
void buildRandomBoard(char8_t ** board);
int32_t rangedRandom(int32_t min, int32_t max);
void searchForWords();
void printBoard(char8_t ** board);
void printWords();
void resetGame(char8_t ** board); // todo get rid of board if not needed in here

void initBoard(char8_t ** board);
char8_t getRandomCharacterFromDie(const char8_t* die);

extern const char8_t* Dice[];


#undef extern