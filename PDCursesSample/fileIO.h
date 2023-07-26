#pragma once

struct Ranking {
    int ranking;
    int score;
    char name[1024];
};
void uploadFileData(char* fileName, Ranking* datas, Ranking* ranking);
void loadFileData(char* fileName, Ranking* datas, Ranking *ranking);
void getFileName(char* fileName);