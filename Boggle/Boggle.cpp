#define BOGGLE_CPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "types.h"
#include "Boggle.h"
#include "Dictionary.h"
//#include "dice.h"
#include "game.h"



int32_t main(int32_t argc, char8_t *argv[])
{
	int32_t numWords;
	time_t t;
	char8_t inChar = 0x00;
	LARGE_INTEGER ticksPerSecond;
	LARGE_INTEGER startTime, endTime, elapsedTime;
#if !INPUT_NEEDED_TO_CONTINUE
	float_t timeToAverage[NUM_GAMES_TO_AVERAGE];
#endif
	// get the high resolution counter's accuracy
	QueryPerformanceFrequency(&ticksPerSecond);

	srand((unsigned int)time(&t));

	TrieList_t* trie = parseDictionaryFile(DICTIONARY_FILE_NAME, &numWords);

	// create the board
	char8_t** board = (char8_t**)malloc(NUM_COLS * sizeof(char8_t*));
	for (uchar8_t col = 0; col < NUM_COLS; col++)
	{
		board[col] = (char8_t*)malloc(NUM_ROWS * sizeof(char8_t));
	}

	bool8_t done = false;
	int32_t gameCounter = 0;

	while (!done)
	{
		initGame(board);
		buildRandomBoard(board);
#if DEBUG_PRINTING_ON
		printBoard(board);
#endif
		QueryPerformanceCounter(&startTime);
		searchForWords();
		QueryPerformanceCounter(&endTime);
		elapsedTime.QuadPart = endTime.QuadPart - startTime.QuadPart;
		float_t timeInMilliseconds = 1000.0f* ((float_t)elapsedTime.QuadPart / (float_t)ticksPerSecond.QuadPart);

#if DEBUG_PRINTING_ON
		printf("\nSearch took %f milliseconds.\n", timeInMilliseconds);
		printWords();
#endif

#if INPUT_NEEDED_TO_CONTINUE
		printf("Press q to quit, any other key to continue:");
		scanf("%c", &inChar);
		fflush(stdin);
		if (inChar == 'q')
			done = true;
		if (!done)
			resetGame(board);
#else 
		if (gameCounter < NUM_GAMES_TO_AVERAGE)
		{
			timeToAverage[gameCounter++] = (float_t)timeInMilliseconds;
			resetGame();
		}
		else
		{
			float average = 0.0f;
			for (int32_t i = 0; i < NUM_GAMES_TO_AVERAGE; ++i)
			{
				average += timeToAverage[i];
			}
			average /= (float)NUM_GAMES_TO_AVERAGE;

#if AVERAGE_PRINTING_ON
			printf("\nThe average of the %d games was %2.4f milliseconds\n", NUM_GAMES_TO_AVERAGE, average);
#endif
			done = true;
		}
#endif
	}
}