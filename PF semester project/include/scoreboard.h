#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#define MAX_PLAYERS 100
void loadScoreboard(char names[][40], int games[], int wins[], int losses[], int draws[], int* count);
void saveScoreboard(char names[][40], int games[], int wins[], int losses[], int draws[], int count);
int findPlayer(char names[][40], int count, const char* name);
void recordResult(char names[][40], int games[], int wins[], int losses[], int draws[], int* count, const char* name, int result);
#endif
