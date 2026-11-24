#include "scoreboard.h"
#include <cstdio>
#include <cstring>
#include <cctype>

static void normalizeName(const char* source, char* destination)
{
	int output = 0;
	int i;
	for (i = 0; source[i] != '\0' && output < 39; ++i)
	{
		unsigned char character = static_cast<unsigned char>(source[i]);
		if (std::isspace(character))
		{
			if (output > 0 && destination[output - 1] != '_') destination[output++] = '_';
		}
		else if (std::isalnum(character) || source[i] == '_' || source[i] == '-')
			destination[output++] = source[i];
	}
	if (output > 0 && destination[output - 1] == '_') --output;
	destination[output] = '\0';
	if (destination[0] == '\0') std::strcpy(destination, "Player");
}

void loadScoreboard(char names[][40], int games[], int wins[], int losses[], int draws[], int* count)
{
	FILE* file = std::fopen("scoreboard.txt", "r");
	*count = 0;
	if (file == 0) return;
	char loadedName[40];
	int loadedGames;
	int loadedWins;
	int loadedLosses;
	int loadedDraws;
	while (std::fscanf(file, "%39s %d %d %d %d", loadedName, &loadedGames, &loadedWins, &loadedLosses, &loadedDraws) == 5)
	{
		char safeName[40];
		normalizeName(loadedName, safeName);
		int index = findPlayer(names, *count, safeName);
		if (index < 0 && *count < MAX_PLAYERS)
		{
			index = *count;
			std::strcpy(names[index], safeName);
			games[index] = wins[index] = losses[index] = draws[index] = 0;
			++(*count);
		}
		if (index >= 0)
		{
			games[index] += loadedGames > 0 ? loadedGames : 0;
			wins[index] += loadedWins > 0 ? loadedWins : 0;
			losses[index] += loadedLosses > 0 ? loadedLosses : 0;
			draws[index] += loadedDraws > 0 ? loadedDraws : 0;
		}
	}
	std::fclose(file);
}

void saveScoreboard(char names[][40], int games[], int wins[], int losses[], int draws[], int count)
{
	FILE* file = std::fopen("scoreboard.tmp", "w");
	int i;
	if (file == 0) return;
	for (i = 0; i < count; ++i)
		std::fprintf(file, "%s %d %d %d %d\n", names[i], games[i], wins[i], losses[i], draws[i]);
	std::fclose(file);
	std::remove("scoreboard.txt");
	std::rename("scoreboard.tmp", "scoreboard.txt");
}

int findPlayer(char names[][40], int count, const char* name)
{
	int i;
	for (i = 0; i < count; ++i)
		if (std::strcmp(names[i], name) == 0) return i;
	return -1;
}

void recordResult(char names[][40], int games[], int wins[], int losses[], int draws[], int* count, const char* name, int result)
{
	char safeName[40];
	normalizeName(name, safeName);
	int index = findPlayer(names, *count, safeName);
	if (index < 0 && *count < MAX_PLAYERS)
	{
		index = *count;
		std::strcpy(names[index], safeName);
		games[index] = wins[index] = losses[index] = draws[index] = 0;
		++(*count);
	}
	if (index < 0) return;
	++games[index];
	if (result == 1) ++wins[index];
	else if (result == -1) ++losses[index];
	else ++draws[index];
	saveScoreboard(names, games, wins, losses, draws, *count);
}
