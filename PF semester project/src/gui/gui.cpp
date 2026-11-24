#include "gui.h"
#include <cstring>
#include <string>

static const sf::Color bg(24, 30, 38);
static const sf::Color panel(42, 52, 62);
static const sf::Color accent(110, 220, 170);
static const sf::Color warm(245, 180, 95);
static const sf::Color textColor(235, 240, 242);

static void text(sf::RenderWindow* window, sf::Font* font, const char* value, unsigned int size, float x, float y, sf::Color color)
{
	sf::Text item(value, *font, size);
	item.setFillColor(color);
	item.setPosition(x, y);
	window->draw(item);
}

static void centered(sf::RenderWindow* window, sf::Font* font, const char* value, unsigned int size, float x, float y, sf::Color color)
{
	sf::Text item(value, *font, size);
	sf::FloatRect bounds = item.getLocalBounds();
	item.setFillColor(color);
	item.setPosition(x - bounds.width / 2.0f - bounds.left, y);
	window->draw(item);
}

int loadGameFont(sf::Font* font)
{
	return font->loadFromFile("C:/Windows/Fonts/arial.ttf");
}

void drawButton(sf::RenderWindow* window, sf::Font* font, sf::FloatRect bounds, const char* value, int selected)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	sf::Vector2f point = window->mapPixelToCoords(mouse);
	sf::RectangleShape shape(sf::Vector2f(bounds.width, bounds.height));
	shape.setPosition(bounds.left, bounds.top);
	shape.setFillColor(selected ? accent : (bounds.contains(point) ? sf::Color(68, 84, 92) : panel));
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(selected ? accent : sf::Color(150, 165, 170));
	window->draw(shape);
	centered(window, font, value, 20, bounds.left + bounds.width / 2.0f, bounds.top + 13.0f, selected ? bg : textColor);
}

void drawMenu(sf::RenderWindow* window, sf::Font* font)
{
	window->clear(bg);
	text(window, font, "TIC-TAC-TOE", 18, 50, 35, accent);
	centered(window, font, "Tic-Tac-Toe with Computer", 42, 500, 140, textColor);
	drawButton(window, font, sf::FloatRect(330, 300, 340, 58), "Play", 0);
	drawButton(window, font, sf::FloatRect(330, 390, 340, 58), "Scoreboard", 0);
	drawButton(window, font, sf::FloatRect(330, 480, 340, 58), "Exit", 0);
}

void drawSettings(sf::RenderWindow* window, sf::Font* font, const char* playerName, int difficulty, char mark, int soundEnabled)
{
	window->clear(bg);
	text(window, font, "GAME SETUP", 30, 60, 35, textColor);
	text(window, font, "Player name", 20, 160, 100, textColor);
	sf::RectangleShape nameBox(sf::Vector2f(500, 52));
	nameBox.setPosition(340, 92);
	nameBox.setFillColor(panel);
	nameBox.setOutlineThickness(1.0f);
	nameBox.setOutlineColor(sf::Color(150, 165, 170));
	window->draw(nameBox);
	text(window, font, playerName[0] == '\0' ? "Enter name" : playerName, 20, 355, 105, playerName[0] == '\0' ? sf::Color(170, 185, 190) : textColor);
	text(window, font, "Difficulty", 20, 160, 180, textColor);
	drawButton(window, font, sf::FloatRect(160, 220, 180, 55), "Easy", difficulty == 1);
	drawButton(window, font, sf::FloatRect(410, 220, 180, 55), "Medium", difficulty == 2);
	drawButton(window, font, sf::FloatRect(660, 220, 180, 55), "Hard", difficulty == 3);
	text(window, font, "Your mark", 20, 160, 310, textColor);
	drawButton(window, font, sf::FloatRect(300, 350, 100, 55), "X", mark == 'X');
	drawButton(window, font, sf::FloatRect(450, 350, 100, 55), "O", mark == 'O');
	drawButton(window, font, sf::FloatRect(600, 350, 250, 55), soundEnabled ? "Sound: ON" : "Sound: OFF", 0);
	drawButton(window, font, sf::FloatRect(350, 500, 300, 55), "Start Game", 0);
	drawButton(window, font, sf::FloatRect(350, 590, 300, 55), "Back", 0);
}

void drawGameScreen(sf::RenderWindow* window, sf::Font* font, char board[3][3], int hoverRow, int hoverColumn, char winner, const char* message, char playerMark, char computerMark)
{
	int row;
	int column;
	window->clear(bg);
	text(window, font, "GAME", 24, 55, 35, accent);
	text(window, font, message, 22, 590, 85, winner == ' ' ? textColor : accent);
	text(window, font, playerMark == 'X' ? "You: X" : "You: O", 18, 590, 135, textColor);
	text(window, font, computerMark == 'X' ? "Computer: X" : "Computer: O", 18, 590, 170, warm);
	for (row = 0; row < 3; ++row)
		for (column = 0; column < 3; ++column)
		{
			float x = 70.0f + column * 155.0f;
			float y = 125.0f + row * 155.0f;
			sf::RectangleShape tile(sf::Vector2f(140, 140));
			tile.setPosition(x, y);
			tile.setFillColor(row == hoverRow && column == hoverColumn && board[row][column] == ' ' ? sf::Color(70, 105, 95) : panel);
			window->draw(tile);
			if (board[row][column] != ' ')
				centered(window, font, board[row][column] == 'X' ? "X" : "O", 78, x + 70, y + 30, board[row][column] == 'X' ? accent : warm);
		}
	if (winner != ' ')
	{
		sf::RectangleShape line(sf::Vector2f(400, 7));
		line.setFillColor(accent);
		if (board[0][0] == winner && board[1][1] == winner && board[2][2] == winner) { line.setPosition(95, 190); line.rotate(45); }
		else if (board[0][2] == winner && board[1][1] == winner && board[2][0] == winner) { line.setPosition(95, 500); line.rotate(-45); }
		else
		{
			for (row = 0; row < 3; ++row) if (board[row][0] == winner && board[row][1] == winner && board[row][2] == winner) { line.setPosition(80, 190 + row * 155); line.rotate(0); }
			for (column = 0; column < 3; ++column) if (board[0][column] == winner && board[1][column] == winner && board[2][column] == winner) { line.setPosition(285 + column * 155, 110); line.rotate(90); }
		}
		window->draw(line);
	}
	drawButton(window, font, sf::FloatRect(590, 470, 300, 55), "Restart (R)", 0);
	drawButton(window, font, sf::FloatRect(590, 545, 300, 55), "Main Menu (Esc)", 0);
}

void drawFinishedScreen(sf::RenderWindow* window, sf::Font* font, char board[3][3], char winner, const char* message, char playerMark, char computerMark)
{
	drawGameScreen(window, font, board, -1, -1, winner, message, playerMark, computerMark);
	text(window, font, "Game over", 18, 590, 215, accent);
	drawButton(window, font, sf::FloatRect(590, 470, 300, 55), "Restart", 0);
	drawButton(window, font, sf::FloatRect(590, 545, 300, 55), "Main Menu", 0);
}

void drawScoreboard(sf::RenderWindow* window, sf::Font* font, char names[][40], int games[], int wins[], int losses[], int draws[], int count, int offset)
{
	int i;
	window->clear(bg);
	text(window, font, "SCOREBOARD", 30, 60, 55, textColor);
	text(window, font, "PLAYER", 16, 80, 145, accent);
	text(window, font, "GAMES", 16, 430, 145, accent);
	text(window, font, "WINS", 16, 550, 145, accent);
	text(window, font, "LOSSES", 16, 650, 145, accent);
	text(window, font, "DRAWS", 16, 780, 145, accent);
	for (i = offset; i < count && i < offset + 10; ++i)
	{
		float y = 190 + (i - offset) * 38.0f;
		text(window, font, names[i], 17, 80, y, textColor);
		text(window, font, std::to_string(games[i]).c_str(), 17, 440, y, textColor);
		text(window, font, std::to_string(wins[i]).c_str(), 17, 565, y, accent);
		text(window, font, std::to_string(losses[i]).c_str(), 17, 675, y, warm);
		text(window, font, std::to_string(draws[i]).c_str(), 17, 805, y, textColor);
	}
	if (count == 0) centered(window, font, "No games recorded yet", 22, 500, 300, textColor);
	drawButton(window, font, sf::FloatRect(350, 620, 300, 55), "Back", 0);
}