#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "difficulty.h"
#include "game.h"
#include "scoreboard.h"

namespace
{
    const unsigned int windowWidth = 1000;
    const unsigned int windowHeight = 720;
    const float boardLeft = 65.f;
    const float boardTop = 225.f;
    const float cellSize = 125.f;

    const sf::Color backgroundColor(25, 32, 38);
    const sf::Color panelColor(39, 49, 56);
    const sf::Color tileColor(54, 70, 72);
    const sf::Color accentColor(119, 213, 171);
    const sf::Color warmColor(246, 190, 112);
    const sf::Color mutedColor(166, 181, 185);

    enum Screen
    {
        Home,
        Scoreboard,
        Setup,
        Playing,
        Finished
    };

    bool loadFont(sf::Font& font)
    {
        const char* paths[] = {
            "assets/fonts/SpaceGrotesk.ttf",
            "../assets/fonts/SpaceGrotesk.ttf",
            "C:/Windows/Fonts/segoeui.ttf",
            "C:/Windows/Fonts/arial.ttf"
        };

        for (const char* path : paths)
        {
            if (font.loadFromFile(path)) return true;
        }
        return false;
    }

    void drawText(sf::RenderWindow& window, const sf::Font& font,
        const std::string& value, unsigned int size, sf::Color color,
        float x, float y)
    {
        sf::Text text(value, font, size);
        text.setFillColor(color);
        text.setPosition(x, y);
        window.draw(text);
    }

    void drawCenteredText(sf::RenderWindow& window, const sf::Font& font,
        const std::string& value, unsigned int size, sf::Color color,
        float centerX, float y)
    {
        sf::Text text(value, font, size);
        text.setFillColor(color);
        const sf::FloatRect bounds = text.getLocalBounds();
        text.setPosition(centerX - bounds.width / 2.f - bounds.left, y);
        window.draw(text);
    }

    void drawButton(sf::RenderWindow& window, const sf::Font& font,
        const sf::FloatRect& bounds, const std::string& value, bool selected,
        sf::Vector2f mouse)
    {
        const bool hovered = bounds.contains(mouse);
        sf::RectangleShape shadow(sf::Vector2f(bounds.width, bounds.height));
        shadow.setPosition(bounds.left, bounds.top + 5.f);
        shadow.setFillColor(sf::Color(12, 18, 21));
        window.draw(shadow);

        sf::RectangleShape shape(sf::Vector2f(bounds.width, bounds.height));
        shape.setPosition(bounds.left, bounds.top);
        shape.setFillColor(selected ? accentColor :
            (hovered ? sf::Color(60, 76, 80) : panelColor));
        shape.setOutlineThickness(1.f);
        shape.setOutlineColor(selected ? accentColor : mutedColor);
        window.draw(shape);

        sf::Text label(value, font, 19);
        label.setFillColor(selected ? backgroundColor : sf::Color::White);
        const sf::FloatRect textBounds = label.getLocalBounds();
        label.setPosition(bounds.left + (bounds.width - textBounds.width) / 2.f - textBounds.left,
            bounds.top + (bounds.height - textBounds.height) / 2.f - textBounds.top - 2.f);
        window.draw(label);
    }

    std::string cleanName(const std::string& name)
    {
        std::size_t first = 0;
        while (first < name.size() && std::isspace(static_cast<unsigned char>(name[first]))) ++first;
        std::size_t last = name.size();
        while (last > first && std::isspace(static_cast<unsigned char>(name[last - 1]))) --last;
        return name.substr(first, last - first);
    }

    void drawRaisedBoard(sf::RenderWindow& window, const sf::Font& font,
        char board[3][3], sf::Vector2f mouse)
    {
        sf::RectangleShape base(sf::Vector2f(cellSize * 3.f, cellSize * 3.f));
        base.setPosition(boardLeft, boardTop + 12.f);
        base.setFillColor(sf::Color(12, 18, 21));
        window.draw(base);

        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                const float x = boardLeft + col * cellSize;
                const float y = boardTop + row * cellSize;
                const bool hovered = sf::FloatRect(x, y, cellSize, cellSize).contains(mouse) && board[row][col] == ' ';

                sf::RectangleShape shadow(sf::Vector2f(cellSize - 9.f, cellSize - 9.f));
                shadow.setPosition(x + 7.f, y + 9.f);
                shadow.setFillColor(sf::Color(10, 15, 17));
                window.draw(shadow);

                sf::RectangleShape tile(sf::Vector2f(cellSize - 12.f, cellSize - 12.f));
                tile.setPosition(x + 2.f, y + 2.f);
                tile.setFillColor(hovered ? sf::Color(69, 91, 87) : tileColor);
                window.draw(tile);

                sf::RectangleShape top(sf::Vector2f(cellSize - 12.f, 3.f));
                top.setPosition(x + 2.f, y + 2.f);
                top.setFillColor(sf::Color(112, 137, 130));
                window.draw(top);

                sf::RectangleShape left(sf::Vector2f(3.f, cellSize - 12.f));
                left.setPosition(x + 2.f, y + 2.f);
                left.setFillColor(sf::Color(112, 137, 130));
                window.draw(left);

                sf::RectangleShape bottom(sf::Vector2f(cellSize - 12.f, 3.f));
                bottom.setPosition(x + 2.f, y + cellSize - 13.f);
                bottom.setFillColor(sf::Color(28, 38, 40));
                window.draw(bottom);

                sf::RectangleShape right(sf::Vector2f(3.f, cellSize - 12.f));
                right.setPosition(x + cellSize - 13.f, y + 2.f);
                right.setFillColor(sf::Color(28, 38, 40));
                window.draw(right);

                if (board[row][col] != ' ')
                {
                    sf::Text mark(std::string(1, board[row][col]), font, 72);
                    mark.setFillColor(board[row][col] == 'X' ? accentColor : warmColor);
                    const sf::FloatRect bounds = mark.getLocalBounds();
                    mark.setPosition(x + (cellSize - bounds.width) / 2.f - bounds.left,
                        y + (cellSize - bounds.height) / 2.f - bounds.top - 4.f);
                    window.draw(mark);
                }
            }
        }
    }
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::Font font;
    if (!loadFont(font))
    {
        std::cerr << "Could not load a font. Put SpaceGrotesk.ttf in assets/fonts/ next to the exe." << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
        "Tic-Tac-Toe", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    std::string playerNames[maxPlayers];
    int gamesPlayed[maxPlayers] = {};
    int wins[maxPlayers] = {};
    int losses[maxPlayers] = {};
    int draws[maxPlayers] = {};
    int playerCount = 0;
    loadScoreboard(playerNames, gamesPlayed, wins, losses, draws, playerCount);

    Screen screen = Screen::Home;
    std::string playerName;
    std::string message;
    std::string saveMessage;
    int difficultyLevel = 1;
    int scoreboardOffset = 0;
    char playerMark = 'X';
    char computerMark = 'O';
    char currentTurn = 'X';
    char board[3][3];
    initializeBoard(board);
    bool nameFieldActive = true;

    const sf::FloatRect scoreboardBounds(330.f, 380.f, 340.f, 64.f);
    const sf::FloatRect playBounds(330.f, 470.f, 340.f, 64.f);
    const sf::FloatRect homeBounds(760.f, 58.f, 180.f, 48.f);
    const sf::FloatRect backBounds(760.f, 58.f, 180.f, 48.f);
    const sf::FloatRect easyBounds(565.f, 285.f, 110.f, 46.f);
    const sf::FloatRect mediumBounds(690.f, 285.f, 110.f, 46.f);
    const sf::FloatRect hardBounds(815.f, 285.f, 110.f, 46.f);
    const sf::FloatRect xBounds(565.f, 375.f, 110.f, 48.f);
    const sf::FloatRect oBounds(690.f, 375.f, 110.f, 48.f);
    const sf::FloatRect startBounds(565.f, 465.f, 360.f, 54.f);
    const sf::FloatRect replayBounds(565.f, 485.f, 360.f, 52.f);

    auto startRound = [&]()
        {
            initializeBoard(board);
            currentTurn = 'X';
            screen = Screen::Playing;
            message = (currentTurn == playerMark) ? "Your turn" : "Computer's turn";
            saveMessage.clear();
        };

    auto finishRound = [&](char winner)
        {
            GameResult result = GameResult::Draw;
            if (winner == playerMark)
            {
                result = GameResult::Win;
                message = playerName + " wins!";
            }
            else if (winner == computerMark)
            {
                result = GameResult::Loss;
                message = "Computer wins";
            }
            else
            {
                message = "It's a draw";
            }

            if (!recordResult(playerNames, gamesPlayed, wins, losses, draws, playerCount,
                playerName, result)) saveMessage = "Could not save scoreboard.txt";
            screen = Screen::Finished;
        };

    auto checkRound = [&]() -> bool
        {
            const char winner = checkWinner(board);
            if (winner != ' ')
            {
                finishRound(winner);
                return true;
            }
            if (isBoardFull(board))
            {
                finishRound(' ');
                return true;
            }
            return false;
        };

    auto playComputerTurn = [&]()
        {
            makeComputerMove(board, computerMark, playerMark, difficultyLevel);
            checkRound();
            if (screen == Screen::Playing)
            {
                currentTurn = playerMark;
                message = "Your turn";
            }
        };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseWheelScrolled && screen == Screen::Scoreboard)
            {
                scoreboardOffset = std::max(0, scoreboardOffset + (event.mouseWheelScroll.delta < 0 ? 1 : -1));
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (screen == Screen::Scoreboard && event.key.code == sf::Keyboard::Down)
                    ++scoreboardOffset;
                else if (screen == Screen::Scoreboard && event.key.code == sf::Keyboard::Up)
                    scoreboardOffset = std::max(0, scoreboardOffset - 1);
                else if (event.key.code == sf::Keyboard::Escape && screen != Screen::Playing)
                    screen = Screen::Home;
            }
            else if (event.type == sf::Event::TextEntered && screen == Screen::Setup && nameFieldActive)
            {
                if (event.text.unicode == 8)
                {
                    if (!playerName.empty()) playerName.pop_back();
                }
                else if (event.text.unicode >= 32 && event.text.unicode < 127 && playerName.size() < 18)
                {
                    playerName += static_cast<char>(event.text.unicode);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                const sf::Vector2f mouse(static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y));

                if (screen == Screen::Home)
                {
                    if (scoreboardBounds.contains(mouse))
                    {
                        scoreboardOffset = 0;
                        screen = Screen::Scoreboard;
                    }
                    else if (playBounds.contains(mouse))
                    {
                        screen = Screen::Setup;
                        playerName.clear();
                        message.clear();
                        nameFieldActive = true;
                    }
                }
                else if (screen == Screen::Scoreboard)
                {
                    if (backBounds.contains(mouse)) screen = Screen::Home;
                }
                else if (screen == Screen::Setup)
                {
                    const sf::FloatRect nameBounds(565.f, 180.f, 360.f, 52.f);
                    nameFieldActive = nameBounds.contains(mouse);
                    if (easyBounds.contains(mouse)) difficultyLevel = 1;
                    if (mediumBounds.contains(mouse)) difficultyLevel = 2;
                    if (hardBounds.contains(mouse)) difficultyLevel = 3;
                    if (xBounds.contains(mouse)) playerMark = 'X';
                    if (oBounds.contains(mouse)) playerMark = 'O';
                    computerMark = (playerMark == 'X') ? 'O' : 'X';

                    if (homeBounds.contains(mouse))
                    {
                        screen = Screen::Home;
                    }
                    else if (startBounds.contains(mouse))
                    {
                        playerName = cleanName(playerName);
                        if (playerName.empty())
                        {
                            message = "Enter your name first";
                        }
                        else
                        {
                            startRound();
                            if (currentTurn != playerMark) playComputerTurn();
                        }
                    }
                }
                else if (screen == Screen::Playing && homeBounds.contains(mouse))
                {
                    screen = Screen::Home;
                }
                else if (screen == Screen::Playing && currentTurn == playerMark)
                {
                    const float boardSize = cellSize * 3.f;
                    if (mouse.x >= boardLeft && mouse.x < boardLeft + boardSize &&
                        mouse.y >= boardTop && mouse.y < boardTop + boardSize)
                    {
                        const int col = static_cast<int>((mouse.x - boardLeft) / cellSize);
                        const int row = static_cast<int>((mouse.y - boardTop) / cellSize);
                        if (board[row][col] == ' ')
                        {
                            board[row][col] = playerMark;
                            if (!checkRound())
                            {
                                currentTurn = computerMark;
                                message = "Computer's turn";
                                playComputerTurn();
                            }
                        }
                    }
                }
                else if (screen == Screen::Finished)
                {
                    if (homeBounds.contains(mouse))
                    {
                        screen = Screen::Home;
                    }
                    else if (replayBounds.contains(mouse))
                    {
                        startRound();
                        if (currentTurn != playerMark) playComputerTurn();
                    }
                }
            }
        }

        const sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        window.clear(backgroundColor);
        drawText(window, font, "TIC-TAC-TOE", 17, accentColor, 58.f, 38.f);

        if (screen == Screen::Home)
        {
            drawCenteredText(window, font, "Tic-Tac-Toe", 52, sf::Color::White, 500.f, 170.f);
            drawCenteredText(window, font, "Pick a page to get started", 20, mutedColor, 500.f, 250.f);
            drawButton(window, font, scoreboardBounds, "Scoreboard", false, mouse);
            drawButton(window, font, playBounds, "Play", false, mouse);
        }
        else if (screen == Screen::Scoreboard)
        {
            drawText(window, font, "PLAYER SCOREBOARD", 31, sf::Color::White, 58.f, 68.f);
            drawButton(window, font, backBounds, "Back", false, mouse);

            sf::RectangleShape tableHeader(sf::Vector2f(880.f, 48.f));
            tableHeader.setPosition(58.f, 160.f);
            tableHeader.setFillColor(panelColor);
            window.draw(tableHeader);
            drawText(window, font, "PLAYER", 16, accentColor, 80.f, 174.f);
            drawText(window, font, "GAMES", 16, accentColor, 430.f, 174.f);
            drawText(window, font, "WON", 16, accentColor, 555.f, 174.f);
            drawText(window, font, "LOST", 16, accentColor, 665.f, 174.f);
            drawText(window, font, "DRAWN", 16, accentColor, 780.f, 174.f);

            int sortedPlayers[maxPlayers];
            for (int index = 0; index < playerCount; ++index) sortedPlayers[index] = index;
            for (int left = 0; left < playerCount - 1; ++left)
            {
                for (int right = left + 1; right < playerCount; ++right)
                {
                    const int leftIndex = sortedPlayers[left];
                    const int rightIndex = sortedPlayers[right];
                    if (wins[rightIndex] > wins[leftIndex] ||
                        (wins[rightIndex] == wins[leftIndex] &&
                            gamesPlayed[rightIndex] > gamesPlayed[leftIndex]))
                    {
                        const int temporary = sortedPlayers[left];
                        sortedPlayers[left] = sortedPlayers[right];
                        sortedPlayers[right] = temporary;
                    }
                }
            }

            const int visibleRows = 10;

            // Clamp the scroll offset before it is used for drawing.
            {
                const int maxOffset = std::max(0,
                    playerCount - visibleRows);
                scoreboardOffset = std::max(0, std::min(scoreboardOffset, maxOffset));
            }

            for (int row = 0; row < visibleRows; ++row)
            {
                const int index = scoreboardOffset + row;
                if (index >= playerCount) break;
                const float y = 216.f + static_cast<float>(row) * 42.f;
                if (row % 2 == 0)
                {
                    sf::RectangleShape stripe(sf::Vector2f(880.f, 40.f));
                    stripe.setPosition(58.f, y - 5.f);
                    stripe.setFillColor(sf::Color(31, 40, 46));
                    window.draw(stripe);
                }
                const int playerIndex = sortedPlayers[index];
                drawText(window, font, playerNames[playerIndex], 17, sf::Color::White, 80.f, y);
                drawText(window, font, std::to_string(gamesPlayed[playerIndex]), 17, sf::Color::White, 445.f, y);
                drawText(window, font, std::to_string(wins[playerIndex]), 17, accentColor, 575.f, y);
                drawText(window, font, std::to_string(losses[playerIndex]), 17, warmColor, 685.f, y);
                drawText(window, font, std::to_string(draws[playerIndex]), 17, mutedColor, 805.f, y);
            }

            if (playerCount == 0)
            {
                drawCenteredText(window, font, "No games recorded yet", 20, mutedColor, 500.f, 260.f);
            }
            else
            {
                drawText(window, font, "Use the mouse wheel or arrow keys to view more players",
                    14, mutedColor, 58.f, 660.f);
            }
        }
        else if (screen == Screen::Setup)
        {
            drawText(window, font, "PLAYER SETUP", 31, sf::Color::White, 58.f, 68.f);
            drawButton(window, font, homeBounds, "Main menu", false, mouse);
            drawText(window, font, "Player name", 17, mutedColor, 565.f, 145.f);

            sf::RectangleShape nameField(sf::Vector2f(360.f, 52.f));
            nameField.setPosition(565.f, 180.f);
            nameField.setFillColor(panelColor);
            nameField.setOutlineThickness(2.f);
            nameField.setOutlineColor(nameFieldActive ? accentColor : mutedColor);
            window.draw(nameField);
            drawText(window, font,
                playerName.empty() ? std::string("Click here and type your name") : playerName,
                17, playerName.empty() ? mutedColor : sf::Color::White, 580.f, 195.f);

            drawText(window, font, "Difficulty", 17, mutedColor, 565.f, 250.f);
            drawButton(window, font, easyBounds, "Easy", difficultyLevel == 1, mouse);
            drawButton(window, font, mediumBounds, "Medium", difficultyLevel == 2, mouse);
            drawButton(window, font, hardBounds, "Hard", difficultyLevel == 3, mouse);

            drawText(window, font, "Choose your mark", 17, mutedColor, 565.f, 340.f);
            drawButton(window, font, xBounds, "X", playerMark == 'X', mouse);
            drawButton(window, font, oBounds, "O", playerMark == 'O', mouse);

            drawButton(window, font, startBounds, "Start game", !cleanName(playerName).empty(), mouse);
            drawText(window, font, "X always takes the first turn.", 15, mutedColor, 565.f, 548.f);
            if (!message.empty()) drawText(window, font, message, 16, warmColor, 565.f, 580.f);

            sf::RectangleShape sampleBoard(sf::Vector2f(365.f, 365.f));
            sampleBoard.setPosition(85.f, 205.f);
            sampleBoard.setFillColor(panelColor);
            sampleBoard.setOutlineThickness(4.f);
            sampleBoard.setOutlineColor(sf::Color(12, 18, 21));
            window.draw(sampleBoard);
            drawCenteredText(window, font, "X", 112, accentColor, 205.f, 265.f);
            drawCenteredText(window, font, "O", 112, warmColor, 325.f, 415.f);
        }
        else
        {
            drawText(window, font, "Tic-Tac-Toe", 31, sf::Color::White, 58.f, 68.f);
            drawButton(window, font, homeBounds, "Main menu", false, mouse);
            drawText(window, font, message, 21, accentColor, 515.f, 160.f);

            // NOTE: build these as std::string first. "text" + char + "text" does
            // pointer arithmetic on a string literal and does not compile.
            const std::string playerLabel = playerName + "  (" + std::string(1, playerMark) + ")";
            const std::string computerLabel = std::string("Computer  (") + computerMark + ")";
            drawText(window, font, playerLabel, 17, sf::Color::White, 515.f, 205.f);
            drawText(window, font, computerLabel, 17, mutedColor, 735.f, 205.f);
            drawRaisedBoard(window, font, board, mouse);

            sf::RectangleShape statsPanel(sf::Vector2f(425.f, 190.f));
            statsPanel.setPosition(515.f, 270.f);
            statsPanel.setFillColor(panelColor);
            window.draw(statsPanel);
            const int playerIndex = findPlayer(playerNames, playerCount, playerName);
            const int playerGames = playerIndex < 0 ? 0 : gamesPlayed[playerIndex];
            const int playerWins = playerIndex < 0 ? 0 : wins[playerIndex];
            const int playerLosses = playerIndex < 0 ? 0 : losses[playerIndex];
            const int playerDraws = playerIndex < 0 ? 0 : draws[playerIndex];
            drawText(window, font, "YOUR RECORD", 17, accentColor, 540.f, 292.f);
            drawText(window, font, "Played   " + std::to_string(playerGames),
                17, sf::Color::White, 540.f, 335.f);
            drawText(window, font, "Won   " + std::to_string(playerWins) +
                "     Lost   " + std::to_string(playerLosses), 17, sf::Color::White, 540.f, 377.f);
            drawText(window, font, "Drawn   " + std::to_string(playerDraws),
                17, sf::Color::White, 540.f, 419.f);

            if (screen == Screen::Finished)
            {
                drawButton(window, font, replayBounds, "Play again", false, mouse);
                if (!saveMessage.empty()) drawText(window, font, saveMessage, 14, warmColor, 515.f, 555.f);
            }
        }

        window.display();
    }

    return 0;
}