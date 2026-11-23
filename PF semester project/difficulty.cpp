#include <cstdlib>
#include "difficulty.h"
static char findWinner(char board[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != ' ')
        {
            return board[row][0];
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != ' ')
        {
            return board[0][col];
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return board[0][0];
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != ' ')
    {
        return board[0][2];
    }

    return ' ';
}
static bool boardIsFull(char board[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}
static int findBestScore(char board[3][3], char computerMark, char playerMark, bool computerTurn)
{
    char winner = findWinner(board);

    if (winner == computerMark)
    {
        return 10;
    }

    if (winner == playerMark)
    {
        return -10;
    }

    if (boardIsFull(board))
    {
        return 0;
    }

    if (computerTurn)
    {
        int bestScore = -1000;

        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (board[row][col] == ' ')
                {
                    board[row][col] = computerMark;
                    int score = findBestScore(board, computerMark, playerMark, false);
                    board[row][col] = ' ';

                    if (score > bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore = 1000;

        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (board[row][col] == ' ')
                {
                    board[row][col] = playerMark;
                    int score = findBestScore(board, computerMark, playerMark, true);
                    board[row][col] = ' ';

                    if (score < bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }

        return bestScore;
    }
}
static bool findSmartMove(char board[3][3], char mark, int& bestRow, int& bestCol)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == ' ')
            {
                board[row][col] = mark;

                if (findWinner(board) == mark)
                {
                    board[row][col] = ' ';
                    bestRow = row;
                    bestCol = col;
                    return true;
                }

                board[row][col] = ' ';
            }
        }
    }

    return false;
}
static void pickRandomMove(char board[3][3], int& row, int& col)
{
    while (true)
    {
        row = rand() % 3;
        col = rand() % 3;

        if (board[row][col] == ' ')
        {
            break;
        }
    }
}
void makeComputerMove(char board[3][3], char computerMark, char playerMark, int difficultyLevel)
{
    int selectedRow = -1;
    int selectedCol = -1;

    if (difficultyLevel == 1)
    {
        pickRandomMove(board, selectedRow, selectedCol);
    }
    else if (difficultyLevel == 2)
    {
        if (!findSmartMove(board, computerMark, selectedRow, selectedCol))
        {
            if (!findSmartMove(board, playerMark, selectedRow, selectedCol))
            {
                pickRandomMove(board, selectedRow, selectedCol);
            }
        }
    }
    else
    {
        int bestScore = -1000;

        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (board[row][col] == ' ')
                {
                    board[row][col] = computerMark;
                    int score = findBestScore(board, computerMark, playerMark, false);
                    board[row][col] = ' ';

                    if (score > bestScore)
                    {
                        bestScore = score;
                        selectedRow = row;
                        selectedCol = col;
                    }
                }
            }
        }
    }

    board[selectedRow][selectedCol] = computerMark;

}