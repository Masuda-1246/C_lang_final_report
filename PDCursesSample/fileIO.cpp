#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <vector>
#pragma comment(lib, "winmm.lib")

#define NUMTHREAD 2
#define USEMUTEX
#define BUFFSIZE 1024
#define CHARBUFF 124
#define BUFFSIZE 1024

typedef struct {
    int ranking, score;
    char name[BUFFSIZE];
} Ranking;

void getGurrentDirectory(char* currentDirectory) {
    GetCurrentDirectory(CHARBUFF, currentDirectory);
}

void getFileName(char* fileName) {
    char currentDirectory[CHARBUFF];
    getGurrentDirectory(currentDirectory);
    char section[CHARBUFF];
    sprintf_s(section, "section1");
    char keyWord[CHARBUFF];
    sprintf_s(keyWord, "file");
    char settingFile[CHARBUFF];
    sprintf_s(settingFile, "%s\\env.ini", currentDirectory);
    GetPrivateProfileString(section, keyWord, "none", fileName, CHARBUFF, settingFile);
}

void loadFileData(char* fileName, Ranking* datas, Ranking* ranking)
{
    FILE* fp;
    char s[BUFFSIZE];
    char* p1;

    errno_t error;
    error = fopen_s(&fp, fileName, "r");
    if (error != 0)
        fprintf_s(stderr, "failed to open");
    else {
        for (int i = 0; i < 10; i++) {
            Ranking* new_ranking = new Ranking();
            fgets(s, BUFFSIZE, fp);
            char delim[] = ", ";
            char* ctx;
            p1 = strtok_s(s, delim, &ctx);
            new_ranking->score = atoi(p1);
            p1 = strtok_s(NULL, delim, &ctx); // 2?ڈȍ~?̕?????????擾 
            size_t len = strlen(p1);
            if (len > 0 && p1[len - 1] == '\n') {
                p1[len - 1] = '\0'; // 改行コードをヌル文字に置き換える
            }
            sprintf_s(new_ranking->name, "%s", p1);
            datas[i] = *new_ranking;
        }
        fclose(fp);
    }
}

void uploadFileData(char* fileName, Ranking* datas, Ranking* ranking) {
    FILE* fp;
    char s[BUFFSIZE];
    errno_t error;
    error = fopen_s(&fp, fileName, "w");
    if (error != 0)
        fprintf_s(stderr, "failed to open");
    else {
        for (int i = 0; i < 10; i++) {
            sprintf_s(s, "%d, %s,\n", datas[i].score, datas[i].name);
            fputs(s, fp);
        }
        fclose(fp);
    }
}