#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include "game.h"
#include "difficulty.h"
#include "scoreboard.h"
#include "gui.h"
#include "audio.h"
static int hit(sf::RenderWindow* window, float left, float top, float width, float height)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f point = window->mapPixelToCoords(mouse);
	return sf::FloatRect(left, top, width, height).contains(point);
}
static void resetGame(char board[3][3], char& winner, char& turn, int& computerWaiting, char* message, char playerMark, sf::Clock& computerClock)
{
	initializeBoard(board);
	winner = ' ';
	turn = 'X';
	computerWaiting = 0;
	std::strcpy(message, "Your turn");
	if (playerMark == 'O')
	{
		computerWaiting = 1;
		computerClock.restart();
		std::strcpy(message, "Computer's turn");
	}
}

int main()
{
	const int MENU = 0;
	const int SETTINGS = 1;
	const int GAME = 2;
	const int SCOREBOARD = 3;
	const int FINISHED = 4;
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Tic-Tac-Toe with Computer");
	sf::Font font;
	char board[3][3];
	char names[MAX_PLAYERS][40];
	int games[MAX_PLAYERS];
	int wins[MAX_PLAYERS];
	int losses[MAX_PLAYERS];
	int draws[MAX_PLAYERS];
	int playerCount;
	int screen = MENU;
	int difficulty = 2;
	int soundEnabled = 1;
	int scoreboardOffset = 0;
	int hoverRow = -1;
	int hoverColumn = -1;
	int computerWaiting = 0;
	char playerMark = 'X';
	char computerMark = 'O';
	char turn = 'X';
	char winner = ' ';
	char message[80] = "Your turn";
	char playerName[40] = "Player";
	sf::Clock computerClock;
	std::srand(static_cast<unsigned int>(std::time(0)));
	initializeBoard(board);
	loadScoreboard(names, games, wins, losses, draws, &playerCount);
	loadGameFont(&font);
	loadAudio();
    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) screen = MENU;
				if ((screen == GAME || screen == FINISHED) && event.key.code == sf::Keyboard::R)
				{
					resetGame(board, winner, turn, computerWaiting, message, playerMark, computerClock);
					screen = GAME;
				}
			}
			if (screen == SETTINGS && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Backspace)
			{
				int length = static_cast<int>(std::strlen(playerName));
				if (length > 0) playerName[length - 1] = '\0';
			}
			if (screen == SETTINGS && event.type == sf::Event::TextEntered && event.text.unicode >= 32 && event.text.unicode < 127)
			{
				int length = static_cast<int>(std::strlen(playerName));
				if (length < 38) { playerName[length] = static_cast<char>(event.text.unicode); playerName[length + 1] = '\0'; }
			}
			if (screen == GAME && event.type == sf::Event::MouseMoved)
			{
				hoverColumn = (event.mouseMove.x >= 70 && event.mouseMove.x < 535) ? (event.mouseMove.x - 70) / 155 : -1;
				hoverRow = (event.mouseMove.y >= 125 && event.mouseMove.y < 590) ? (event.mouseMove.y - 125) / 155 : -1;
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				float x = static_cast<float>(event.mouseButton.x);
				float y = static_cast<float>(event.mouseButton.y);
				if (screen == MENU)
				{
					if (hit(&window, 330, 300, 340, 58)) { screen = SETTINGS; playerName[0] = '\0'; }
					else if (hit(&window, 330, 390, 340, 58)) { screen = SCOREBOARD; scoreboardOffset = 0; }
					else if (hit(&window, 330, 480, 340, 58)) window.close();
				}
				else if (screen == SETTINGS)
				{
					if (hit(&window, 160, 220, 180, 55)) difficulty = 1;
					if (hit(&window, 410, 220, 180, 55)) difficulty = 2;
					if (hit(&window, 660, 220, 180, 55)) difficulty = 3;
					if (hit(&window, 300, 350, 100, 55)) { playerMark = 'X'; computerMark = 'O'; }
					if (hit(&window, 450, 350, 100, 55)) { playerMark = 'O'; computerMark = 'X'; }
					if (hit(&window, 600, 350, 250, 55)) { soundEnabled = (soundEnabled == 0) ? 1 : 0; setSoundEnabled(soundEnabled); }
					if (hit(&window, 350, 500, 300, 55))
					{
						if (playerName[0] == '\0') std::strcpy(playerName, "Player");
						resetGame(board, winner, turn, computerWaiting, message, playerMark, computerClock);
						screen = GAME;
					}
					else if (hit(&window, 350, 590, 300, 55)) screen = MENU;
				}
				else if (screen == SCOREBOARD && hit(&window, 350, 620, 300, 55)) screen = MENU;
				else if ((screen == GAME || screen == FINISHED) && hit(&window, 590, 470, 300, 55))
				{
					resetGame(board, winner, turn, computerWaiting, message, playerMark, computerClock);
					screen = GAME;
				}
				else if ((screen == GAME || screen == FINISHED) && hit(&window, 590, 545, 300, 55)) screen = MENU;
				else if (screen == GAME && turn == playerMark && x >= 70 && x < 535 && y >= 125 && y < 590)
				{
					int column = static_cast<int>((x - 70) / 155);
					int row = static_cast<int>((y - 125) / 155);
					if (placeMark(board, row, column, playerMark))
					{
						playClickSound();
						winner = checkWinner(board);
						if (winner == playerMark) { recordResult(names, games, wins, losses, draws, &playerCount, playerName, 1); playWinSound(); std::strcpy(message, "You Win!"); screen = FINISHED; }
						else if (isBoardFull(board)) { recordResult(names, games, wins, losses, draws, &playerCount, playerName, 0); playDrawSound(); std::strcpy(message, "It is a Draw"); screen = FINISHED; }
						else { turn = computerMark; computerWaiting = 1; computerClock.restart(); std::strcpy(message, "Computer's turn"); }
					}
				}
			}
		}
		if (screen == GAME && computerWaiting && computerClock.getElapsedTime().asSeconds() > 0.35f)
		{
			makeComputerMove(board, computerMark, playerMark, difficulty);
			playClickSound(); computerWaiting = 0; winner = checkWinner(board);
			if (winner == computerMark) { recordResult(names, games, wins, losses, draws, &playerCount, playerName, -1); playLoseSound(); std::strcpy(message, "Computer Wins"); screen = FINISHED; }
			else if (isBoardFull(board)) { recordResult(names, games, wins, losses, draws, &playerCount, playerName, 0); playDrawSound(); std::strcpy(message, "It is a Draw"); screen = FINISHED; }
			else { turn = playerMark; std::strcpy(message, "Your turn"); }
		}
		if (screen == MENU) drawMenu(&window, &font);
		else if (screen == SETTINGS) drawSettings(&window, &font, playerName, difficulty, playerMark, soundEnabled);
		else if (screen == SCOREBOARD) drawScoreboard(&window, &font, names, games, wins, losses, draws, playerCount, scoreboardOffset);
		else if (screen == GAME) drawGameScreen(&window, &font, board, hoverRow, hoverColumn, winner, message, playerMark, computerMark);
		else drawFinishedScreen(&window, &font, board, winner, message, playerMark, computerMark);
		window.display();
	}
	return 0;
}
