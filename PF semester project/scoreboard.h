#pragma once
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>

const int maxPlayers = 100;

enum GameResult
{
    Win,
    Loss,
    Draw
};

void loadScoreboard(std::string names[], int gamesPlayed[], int wins[], int losses[], int draws[],
    int& playerCount, const std::string& fileName = "scoreboard.txt");
bool saveScoreboard(const std::string names[], const int gamesPlayed[], const int wins[],
    const int losses[], const int draws[], int playerCount,
    const std::string& fileName = "scoreboard.txt");
int findPlayer(const std::string names[], int playerCount, const std::string& playerName);
bool recordResult(std::string names[], int gamesPlayed[], int wins[], int losses[], int draws[],
    int& playerCount, const std::string& playerName, GameResult result,
    const std::string& fileName = "scoreboard.txt");

#endif