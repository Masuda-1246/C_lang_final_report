#include "tetris.h"
#include "name.h"
#include "fileIO.h"
#include "ranking.h"

void initializeApp();
int gameRun();
void newName(char* name);
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