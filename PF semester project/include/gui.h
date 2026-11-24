#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
int loadGameFont(sf::Font* font);
void drawMenu(sf::RenderWindow* window, sf::Font* font);
void drawSettings(sf::RenderWindow* window, sf::Font* font, const char* playerName, int difficulty, char mark, int soundEnabled);
void drawGameScreen(sf::RenderWindow* window, sf::Font* font, char board[3][3], int hoverRow, int hoverColumn, char winner, const char* message, char playerMark, char computerMark);
void drawFinishedScreen(sf::RenderWindow* window, sf::Font* font, char board[3][3], char winner, const char* message, char playerMark, char computerMark);
void drawScoreboard(sf::RenderWindow* window, sf::Font* font, char names[][40], int games[], int wins[], int losses[], int draws[], int count, int offset);
void drawButton(sf::RenderWindow* window, sf::Font* font, sf::FloatRect bounds, const char* text, int selected);
#endif