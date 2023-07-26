#include "tetris.h"
#include "name.h"
#include "fileIO.h"
#include "ranking.h"

void InitializeApp();
int GameRun();
void newName(char* name);
void getFileName(char* fileName);
void showRanking(int score, char* name);


int main() {
    int score = 0;
    InitializeApp();
    char name[1024];
    newName(name);
    score = GameRun();
    showRanking(score, name);
    return 0;
}