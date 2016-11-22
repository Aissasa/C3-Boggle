
#define GAME_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <assert.h>

#include "types.h"
#include "Boggle.h"
#include "Dictionary.h"
#include "dice.h"
#include "game.h"

// creates a word node
wordListT * createWord(char8_t * word, TrieNode_t* sourceNode)
{
	wordListT* newWord = (wordListT*)malloc(sizeof(wordListT));

	newWord->word = (char8_t*)malloc(sizeof(strlen(word) + 1));
	strcpy(newWord->word, word);
	newWord->sourceNode = sourceNode;
	newWord->nextWordNode = nullptr;

	return newWord;
}

// adds a word node to the end of the list
void addWordToEndList(wordListT** list, char8_t * word, TrieNode_t* sourceNode)
{
	if (*list == nullptr)
	{
		*list = createWord(word, sourceNode);
	}
	else
	{
		wordListT* current = *list;

		while (current->nextWordNode != nullptr)
		{
			current = current->nextWordNode;
		}

		assert(current != nullptr);

		current->nextWordNode = createWord(word, sourceNode);
	}
}

// initializes the game
void initGame(char8_t ** board)
{
	topOfWordList = nullptr;
	initBoard(board);
}

// build a random board from the random dice characters
void buildRandomBoard(char8_t ** board)
{
	uchar8_t dieCounter = 0;

	while (dieCounter < NUM_DICE)
	{
		int32_t row = rangedRandom(0, NUM_ROWS - 1);
		int32_t col = rangedRandom(0, NUM_COLS - 1);

		// if already set, try again
		if (board[row][col])
		{
			continue;
		}

		board[row][col] = getRandomCharacterFromDie(Dice[dieCounter++]);
	}

#if DEBUG
	char8_t b[5][5] = { 'V', 'E', 'O', 'I', 'I', 'S', 'N', 'Q', 'S', 'N', 'I', 'H', 'R', 'N', 'D', 'Q', 'K', 'S', 'F', 'O', 'M', 'U', 'M', 'E', 'Z' };
	for (uchar8_t i = 0; i < 5; i++)
	{
		for (uchar8_t j = 0; j < 5; j++)
		{
			board[i][j] = b[i][j];
		}
	}
#endif // DEBUG

}

// prints the board in the console
void printBoard(char8_t ** board)
{
#if DEBUG_PRINTING_ON
	printf("-----------------Board-------------------\n");
	for (uchar8_t row = 0; row < NUM_ROWS; row++)
	{
		for (uchar8_t col = 0; col < NUM_COLS; col++)
		{
			printf("%2c", *(*(board + row) + col));
		}
		printf("\n");
	}
	printf("------------------------------------------\n");

#endif
}

// prints the words found in the board to the console
void printWords()
{
#if DEBUG_PRINTING_ON

	if (topOfWordList == nullptr)
	{
		printf("\nThere are no words in this board\n");
	}
	else
	{
		printf("\nThe words on the board are:\n");

		wordListT* current = topOfWordList;

		while (current != nullptr)
		{
			printf("\n%s", current->word);

			current = current->nextWordNode;
		}
	}
#endif
}

// resets found words and frees memory occupied by words list
void resetGame()
{
	wordListT* currentNodeInList = topOfWordList;

	while (currentNodeInList != nullptr)
	{
		currentNodeInList->sourceNode->isFound = false;
		wordListT* tempNodePtr = currentNodeInList;
		currentNodeInList = currentNodeInList->nextWordNode;

		free(tempNodePtr);
	}


}

// searches for valid words in the board
void searchForWords(char8_t ** board, TrieList_t* trie)
{
	// create path
	uchar8_t** pathTaken = (uchar8_t**)malloc(NUM_COLS * sizeof(uchar8_t*));
	for (uchar8_t col = 0; col < NUM_ROWS; col++)
	{
		pathTaken[col] = (uchar8_t*)malloc(NUM_ROWS * sizeof(uchar8_t));

	}

	// initialize path
	for (uchar8_t i = 0; i < NUM_ROWS; i++)
	{
		for (uchar8_t j = 0; j < NUM_COLS; j++)
		{
			pathTaken[i][j] = 0;
		}
	}

	// process the board
	for (uchar8_t row = 0; row < NUM_ROWS; row++)
	{
		for (uchar8_t col = 0; col < NUM_COLS; col++)
		{
			TrieList_t* currentTrieList = getTrieListByChar(trie, board[row][col]);

			// initialize word
			char8_t currentWord[NUM_DICE] = "";

			// navigate through the board from current spot to find words
			navigateBoard(currentTrieList->characterNode, board, row, col, currentWord, pathTaken);
		}
	}
	// free allocated memory for path taken
	for (uchar8_t col = 0; col < NUM_ROWS; col++)
	{
		free(pathTaken[col]);
	}

	free(pathTaken);
}

// navigates all of the possible paths that may lead to a word in a board from a certain die and adds the word if it's valid
void navigateBoard(TrieNode_t* characterNode, char8_t ** board, uchar8_t row, uchar8_t col, char8_t* currentWord, uchar8_t** pathTaken)
{
	// make a copy of the current word
	char8_t newWord[NUM_DICE] = "";
	strcpy(newWord, currentWord);

	// add the char to the current word
	char8_t c[] = { characterNode->character, '\0' };
	strcat(newWord, c);

	if (characterNode->character == 'Q')
	{
		return navigateBoard(getTrieNodeByChar(characterNode ,'U'), board, row, col, newWord, pathTaken);
	}

	// mark the current die as processed
	pathTaken[row][col] = 1;

	// add the word if it exceeds the min length and it's a word
	if (strlen(newWord) >= MIN_ACCEPTABLE_WORD_LENGTH && !characterNode->isFound && characterNode->endOfWord)
	{
		addWordToEndList(&topOfWordList, newWord, characterNode);
		characterNode->isFound = true;
	}

	for (char8_t cRow = -1; cRow <= 1; cRow++)
	{
		for (char8_t cCol = -1; cCol <= 1; cCol++)
		{
			if(cRow == 0 && cCol == 0)
				continue;

			char8_t tempRow = row + cRow;
			char8_t tempCol = col + cCol;

			if (tempRow >= 0 && tempRow <NUM_ROWS && tempCol >=0 && tempCol < NUM_COLS && !pathTaken[tempRow][tempCol])
			{
				// process that char on the board if there are corresponding words for it
				TrieNode_t* nextNode = getTrieNodeByChar(characterNode, board[tempRow][tempCol]);
				if (nextNode != nullptr)
				{
					navigateBoard(nextNode, board, tempRow, tempCol, newWord, pathTaken);
				}
			}
		}
	}

	pathTaken[row][col] = 0;
}

// returns a ranged random number
int32_t rangedRandom(int32_t min, int32_t max)
{
	return rand() % (max - min + 1) + min;
}

// initializes the board
void initBoard(char8_t** board)
{
	for (uchar8_t row = 0; row < NUM_ROWS; row++)
	{
		for (uchar8_t col = 0; col < NUM_COLS; col++)
		{
			board[row][col] = 0;
		}
	}
}

// returns a random character from a die
char8_t getRandomCharacterFromDie(const char8_t* die)
{
	int32_t randomIndex = rangedRandom(0, DIE_NUM_CHAR - 1);
	return *(die + randomIndex);
}
