
#define GAME_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "types.h"
#include "Boggle.h"
#include "Dictionary.h"
#include "dice.h"
#include "game.h"

void resetGame(char8_t ** board)
{

}

void initGame(char8_t ** board)
{
	initBoard(board);
}

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
}

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

void printWords()
{
#if DEBUG_PRINTING_ON

#endif
}


void searchForWords()
{
	// todo maybe get rid of this
	////just taking some time here to make sure the timer is working properly
	//float j = 0.0f;
	//for (int i = 0; i < 100000; ++i)
	//	j += ((float)rand()) / 100000.0f;

	//printf("j=%f", j);

	// urgent work on this

}

int32_t rangedRandom(int32_t min, int32_t max)
{
	return rand() % (max - min + 1) + min;
}

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

char8_t getRandomCharacterFromDie(const char8_t* die)
{
	int32_t randomIndex = rangedRandom(0, DIE_NUM_CHAR - 1);
	return *(die + randomIndex);
}

