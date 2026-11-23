#include "scoreboard.h"

#include <fstream>
#include <iomanip>

void loadScoreboard(std::string names[], int gamesPlayed[], int wins[], int losses[], int draws[],
    int& playerCount, const std::string& fileName)
{
    std::ifstream input(fileName);
    playerCount = 0;

    while (playerCount < maxPlayers &&
        input >> std::quoted(names[playerCount]) >> gamesPlayed[playerCount] >> wins[playerCount]
        >> losses[playerCount] >> draws[playerCount])
    {
        ++playerCount;
    }
}

bool saveScoreboard(const std::string names[], const int gamesPlayed[], const int wins[],
    const int losses[], const int draws[], int playerCount, const std::string& fileName)
{
    std::ofstream output(fileName);
    if (!output)
    {
        return false;
    }

    for (int index = 0; index < playerCount; ++index)
    {
        output << std::quoted(names[index]) << ' '
            << gamesPlayed[index] << ' '
            << wins[index] << ' '
            << losses[index] << ' '
            << draws[index] << '\n';
    }

    return static_cast<bool>(output);
}

int findPlayer(const std::string names[], int playerCount, const std::string& playerName)
{
    for (int index = 0; index < playerCount; ++index)
    {
        if (names[index] == playerName) return index;
    }

    return -1;
}

bool recordResult(std::string names[], int gamesPlayed[], int wins[], int losses[], int draws[],
    int& playerCount, const std::string& playerName, GameResult result, const std::string& fileName)
{
    if (playerName.empty())
    {
        return false;
    }

    int playerIndex = findPlayer(names, playerCount, playerName);
    if (playerIndex < 0)
    {
        if (playerCount >= maxPlayers) return false;
        playerIndex = playerCount++;
        names[playerIndex] = playerName;
        gamesPlayed[playerIndex] = 0;
        wins[playerIndex] = 0;
        losses[playerIndex] = 0;
        draws[playerIndex] = 0;
    }

    ++gamesPlayed[playerIndex];

    if (result == GameResult::Win)
    {
        ++wins[playerIndex];
    }
    else if (result == GameResult::Loss)
    {
        ++losses[playerIndex];
    }
    else
    {
        ++draws[playerIndex];
    }

    return saveScoreboard(names, gamesPlayed, wins, losses, draws, playerCount, fileName);
}