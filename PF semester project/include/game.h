#ifndef GAME_H
#define GAME_H

void initializeBoard(char board[3][3]);
int placeMark(char board[3][3], int row, int column, char mark);
char checkWinner(char board[3][3]);
int isBoardFull(char board[3][3]);

#endif
