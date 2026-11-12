#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;

int main()
{
    char board[3][3];
    char playerMark;
    char computerMark;
    char winner = ' ';
    char currentTurn;

    srand(time(0));

    cout << "===== TIC TAC TOE =====" << endl;

    cout << "Choose your mark (X or O): ";
    cin >> playerMark;

    while (playerMark != 'X' && playerMark != 'x' &&
        playerMark != 'O' && playerMark != 'o')
    {
        cout << "Please choose only X or O: ";
        cin >> playerMark;
    }

    if (playerMark == 'x')
    {
        playerMark = 'X';
    }
    else if (playerMark == 'o')
    {
        playerMark = 'O';
    }

    if (playerMark == 'X')
    {
        computerMark = 'O';
    }
    else
    {
        computerMark = 'X';
    }

    initializeBoard(board);

    if (playerMark == 'X')
    {
        currentTurn = 'X';
    }
    else
    {
        currentTurn = 'X';
    }

    cout << endl << "You are playing as " << playerMark << endl;
    cout << "Computer is playing as " << computerMark << endl;
    cout << "X always gets the first turn." << endl;

    while (winner == ' ' && isBoardFull(board) == false)
    {
        displayBoard(board);

        if (currentTurn == playerMark)
        {
            cout << "Your turn." << endl;
            playerMove(board, playerMark);
            currentTurn = computerMark;
        }
        else
        {
            cout << "Computer's turn." << endl;
            computerMove(board, computerMark);
            currentTurn = playerMark;
        }

        winner = checkWinner(board);
    }

    displayBoard(board);

    if (winner == playerMark)
    {
        cout << "Congratulations! You win!" << endl;
    }
    else if (winner == computerMark)
    {
        cout << "Computer wins!" << endl;
    }
    else
    {
        cout << "It's a draw!" << endl;
    }

    return 0;
}