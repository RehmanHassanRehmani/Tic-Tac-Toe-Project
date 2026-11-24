#include "game.h"

void initializeBoard(char board[3][3])
{
	int row;
	int column;
	for (row = 0; row < 3; ++row)
		for (column = 0; column < 3; ++column)
			board[row][column] = ' ';
}

int placeMark(char board[3][3], int row, int column, char mark)
{
	if (row < 0 || row > 2 || column < 0 || column > 2 || board[row][column] != ' ')
		return 0;
	board[row][column] = mark;
	return 1;
}

char checkWinner(char board[3][3])
{
	int i;
	for (i = 0; i < 3; ++i)
	{
		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
	}
	if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
	if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];
	return ' ';
}

int isBoardFull(char board[3][3])
{
	int row;
	int column;
	for (row = 0; row < 3; ++row)
		for (column = 0; column < 3; ++column)
			if (board[row][column] == ' ') return 0;
	return 1;
}
