#ifndef GAME_H
#define GAME_H
void initializeBoard(char board[3][3]);
void displayBoard(char board[3][3]);
void playerMove(char board[3][3], char playerMark);
char checkWinner(char board[3][3]);
bool isBoardFull(char board[3][3]);
#endif