#include "difficulty.h"
#include "game.h"
#include <cstdlib>
static int scoreBoard(char board[3][3], char computer, char player, bool computerTurn)
{
	char winner = checkWinner(board);
	int best;
	int score;

	if (winner == computer) return 10;
	if (winner == player) return -10;
	if (isBoardFull(board)) return 0;

	best = computerTurn ? -1000 : 1000;
	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			if (board[row][column] == ' ')
			{
				board[row][column] = computerTurn ? computer : player;
				score = scoreBoard(board, computer, player, !computerTurn);
				board[row][column] = ' ';
				if (computerTurn && score > best) best = score;
				if (!computerTurn && score < best) best = score;
			}
		}
	}
	return best;
}
static int winningMove(char board[3][3], char mark, int* resultRow, int* resultColumn)
{
	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			if (board[row][column] == ' ')
			{
				board[row][column] = mark;
				if (checkWinner(board) == mark)
				{
					board[row][column] = ' ';
					*resultRow = row;
					*resultColumn = column;
					return 1;
				}
				board[row][column] = ' ';
			}
		}
	}
	return 0;
}
void makeComputerMove(char board[3][3], char computerMark, char playerMark, int difficulty)
{
	int row = -1;
	int column = -1;
	int bestScore;
	int score;
	int bestRow = -1;
	int bestColumn = -1;

	if (difficulty == 1)
	{
		do { row = std::rand() % 3; column = std::rand() % 3; } while (board[row][column] != ' ');
	}
	else if (difficulty == 2)
	{
		if (!winningMove(board, computerMark, &row, &column) &&
			!winningMove(board, playerMark, &row, &column))
		{
			do { row = std::rand() % 3; column = std::rand() % 3; } while (board[row][column] != ' ');
		}
	}
	else
	{
		bestScore = -1000;
		for (int r = 0; r < 3; ++r)
		{
			for (int c = 0; c < 3; ++c)
			{
				if (board[r][c] == ' ')
				{
					board[r][c] = computerMark;
					score = scoreBoard(board, computerMark, playerMark, false);
					board[r][c] = ' ';
					if (score > bestScore)
					{
						bestScore = score;
						bestRow = r;
						bestColumn = c;
					}
				}
			}
		}
		row = bestRow;
		column = bestColumn;
	}

	if (row >= 0 && column >= 0) board[row][column] = computerMark;
}
