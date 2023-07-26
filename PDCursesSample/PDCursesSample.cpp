#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <curses.h>
#include <Windows.h>

#include "tetris.h"
#include "name.h"
#include "fileIO.h"
#include "ranking.h"

void initializeApp();
int gameRun();
void newName(char* name);
void showEndScrean(int score, char* name);
void uploadFileData(char* fileName);
void loadFileData(char* fileName);
void getFileName(char* fileName);
void showRanking(int score, char* name);



int main() {
    int score = 0;
    initializeApp();
    char name[1024];
    newName(name);
    score = gameRun();
    showRanking(score, name);
    return 0;
}