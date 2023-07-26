#include <curses.h>
#include <Windows.h>

#include "fileIO.h"
#include "ranking.h"

void uploadFileData(char* fileName, Ranking* datas, Ranking* ranking);
void loadFileData(char* fileName, Ranking* datas, Ranking* ranking);
void getFileName(char* fileName);


void showRanking(int score, char* name) {
    initscr();
    cbreak();
    noecho();
    Ranking* ranking = new Ranking();
    Ranking datas[10];
    char file_name[100];
    getFileName(file_name); 
    ranking->score = score;
    sprintf_s(ranking->name, "%s", name);
    loadFileData(file_name, datas, ranking);
    printw("%s's score is %d\n", ranking->name, ranking->score);
    printw("Ranking \n");
    for (int i = 0; i < 10; i++) {
        if (datas[i].score < ranking->score) {
            for (int j = 9; j > i; j--) {
                datas[j] = datas[j - 1];
            }
            datas[i] = *ranking;
            break;
        }
    }
    uploadFileData(file_name, datas, ranking);
    for (int i = 0; i < 10; i++) {
        printw("%d %s %d\n", i + 1, datas[i].name, datas[i].score);
    }
    refresh();
    getch();
    endwin();
}
