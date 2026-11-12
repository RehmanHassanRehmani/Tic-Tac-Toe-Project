#include <iostream>
#include <cstdlib>
#include "game.h"

using namespace std;

void initializeBoard(char board[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            board[row][col] = ' ';
        }
    }
}

void displayBoard(char board[3][3])
{
    cout << endl;

    for (int row = 0; row < 3; row++)
    {
        cout << " ";

        for (int col = 0; col < 3; col++)
        {
            cout << board[row][col];

            if (col < 2)
            {
                cout << " | ";
            }
        }

        cout << endl;

        if (row < 2)
        {
            cout << "---+---+---" << endl;
        }
    }

    cout << endl;
}

void playerMove(char board[3][3], char playerMark)
{
    int position;
    int row;
    int col;

    while (true)
    {
        cout << "Choose a position (1-9): ";
        cin >> position;

        if (position < 1 || position > 9)
        {
            cout << "Invalid position. Choose from 1 to 9." << endl;
        }
        else
        {
            row = (position - 1) / 3;
            col = (position - 1) % 3;

            if (board[row][col] != ' ')
            {
                cout << "This position is already filled. Try again." << endl;
            }
            else
            {
                board[row][col] = playerMark;
                break;
            }
        }
    }
}

void computerMove(char board[3][3], char computerMark)
{
    int position;
    int row;
    int col;

    while (true)
    {
        position = rand() % 9 + 1;

        row = (position - 1) / 3;
        col = (position - 1) % 3;

        if (board[row][col] == ' ')
        {
            board[row][col] = computerMark;
            cout << "Computer placed " << computerMark << " at position "
                << position << endl;
            break;
        }
    }
}

char checkWinner(char board[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2] &&
            board[row][0] != ' ')
        {
            return board[row][0];
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col] &&
            board[0][col] != ' ')
        {
            return board[0][col];
        }
    }

    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != ' ')
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

bool isBoardFull(char board[3][3])
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