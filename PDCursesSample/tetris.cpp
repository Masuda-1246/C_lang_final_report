#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <curses.h>
#include <Windows.h>

#define FIELD_WIDTH (10)
#define FIELD_HEIGHT (20)

#define SHAPE_WIDTH_MAX (4)
#define SHAPE_HEIGHT_MAX (4)

#define X 50
#define Y 3

int hold_status = 0;

enum {
    SHAPE_I,
    SHAPE_O,
    SHAPE_S,
    SHAPE_Z,
    SHAPE_L,
    SHAPE_J,
    SHAPE_T,
};

typedef struct {
    int width, height, type;
    int pattern[SHAPE_HEIGHT_MAX][SHAPE_WIDTH_MAX];
} SHAPE;

typedef struct {
    int x, y;
    SHAPE shape;
} MINO;

SHAPE shapes[7]{
    {
        4, 4, 1,
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
        }
    },
    {
        2, 2, 2,
        {
            {1, 1},
            {1, 1},
        }
    },
    {
        3, 3, 3,
        {
            {0, 1, 1},
            {1, 1, 0},
            {0, 0, 0}
         }
    },
    {
        3, 3, 4,
        {
            {1, 1, 0},
            {0, 1, 1},
            {0, 0, 0}
        }
    },
    {
        3, 3, 5,
        {
            {0, 0, 1},
            {1, 1, 1},
            {0, 0, 0}
        }
    },
    {
        3, 3, 6,
        {
            {1, 0, 0},
            {1, 1, 1},
            {0, 0, 0}
        }
    },
    {
        3, 3, 7,
        {
            {0, 1, 0},
            {1, 1, 1},
            {0, 0, 0}
        }
    },
};

MINO mino;
MINO nextMino;
MINO holdMino;
int field[FIELD_HEIGHT][FIELD_WIDTH];
int screan[FIELD_HEIGHT][FIELD_WIDTH];

bool MinoIntercectField() {
    int y = 0, x = 0;
    for (y = 0; y < mino.shape.height; y++) {
        for (x = 0; x < mino.shape.width; x++) {
            if (mino.shape.pattern[y][x]) {
                if ((mino.y + y >= FIELD_HEIGHT) || (mino.y + y < 0) || (mino.x + x < 0) || (mino.x + x >= FIELD_WIDTH)) return true;
                if (field[mino.y + y][mino.x + x]) return true;
            }
        }
    }
    return false;
}

void DrawScrean() {
    memcpy(screan, field, sizeof field);
    int y = 0, x = 0;
    for (y = 0; y < mino.shape.height; y++) {
        for (x = 0; x < mino.shape.width; x++) {
            if (mino.shape.pattern[y][x]) {
                screan[mino.y + y][mino.x + x] = mino.shape.type;
            }
        }
    }
    for (y = 0; y < FIELD_HEIGHT; y++) {
        mvprintw(y + Y, 0+X, "□");
        for (x = 0; x < FIELD_WIDTH + 1; x++) {
            attron(COLOR_PAIR(screan[y][x]));
            if (screan[y][x]) mvprintw(y + Y, x * 2 + 2 + X, "■");
            attroff(COLOR_PAIR(screan[y][x]));
        }
        mvprintw(y+Y, x * 2 + X, "□");
    }
    for (x = 0; x < FIELD_WIDTH + 2; x++) {
        mvprintw(y + Y, x * 2 + X, "□");
    }
}

int InitMino(int next) {
    int randam = rand() % 7;
    mino.shape = shapes[next];
    mino.x = FIELD_WIDTH / 2 - mino.shape.width / 2;
    mino.y = 0;
    return randam;
}

int Init() {
    memset(field, 0, sizeof field);
    int next = InitMino(rand() % 7);
    DrawScrean();
    return next;
}

void DrawField() {
    int y = 0, x = 0;
    for (y = 0; y < FIELD_HEIGHT; y++) {
        for (x = 0; x < FIELD_WIDTH; x++) {
            mvprintw(y, 50 + x + X, "%d", screan[y][x]);
        }
    }
}

void DrawNextMino(int next) {
    int y = 0, x = 0;
    nextMino.shape = shapes[next];
    mvprintw(2 + Y, 26 + X, "next");
    for (y = 0; y < nextMino.shape.height; y++) {
        for (x = 0; x < nextMino.shape.width; x++) {
            attron(COLOR_PAIR(nextMino.shape.type));
            if (nextMino.shape.pattern[y][x]) mvprintw(y + 4 + Y, 26 + x * 2 + X, "■");
            attroff(COLOR_PAIR(nextMino.shape.type));
        }
    }
}

void DrawHoldMino(int status) {
    int y = 0, x = 0;
    mvprintw(2 + Y,X-12, "hold");
    if (status) {
        for (y = 0; y < holdMino.shape.height; y++) {
            for (x = 0; x < holdMino.shape.width; x++) {
                attron(COLOR_PAIR(holdMino.shape.type));
                if (holdMino.shape.type != 0 && holdMino.shape.pattern[y][x]) mvprintw(y + 4 + Y, x * 2 + X - 12, "■");
                attroff(COLOR_PAIR(holdMino.shape.type));
            }
        }
    }
    
}

void HoldFlow(int* next) {
    int y = 0, x = 0;
    int type = mino.shape.type - 1;
    if (hold_status == 1) {
        InitMino(holdMino.shape.type - 1);
        holdMino.shape = shapes[type];    
    }
    else if (hold_status == 0) {
        holdMino.shape = shapes[type];
        *next = InitMino(*next);
    }
    
}


void InitializeApp() {
    initscr();
    cbreak();
    noecho();
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    keypad(stdscr, TRUE);
    srand((unsigned int)time(NULL));
}

void KeyAction(int key, int* next) {
    switch (key) {
    case KEY_RIGHT: mino.x++; break;
    case KEY_LEFT: mino.x--; break;
    case KEY_DOWN: mino.y++; break;
    case KEY_UP: {
        MINO newMino = mino;
        for (int y = 0; y < mino.shape.height; y++) {
            for (int x = 0; x < mino.shape.width; x++) {
                newMino.shape.pattern[mino.shape.width - x - 1][y] = mino.shape.pattern[y][x];
            }
        }
        mino = newMino;
    }
               break;
    default: {     
        HoldFlow(next);
        hold_status = 2;
    }
           break;
    }
}

int CompleteFlow(int* next, int* score) {
    for (int y = 0; y < mino.shape.height; y++) {
        for (int x = 0; x < mino.shape.width; x++) {
            if (mino.shape.pattern[y][x]) {
                field[mino.y + y][mino.x + x] = mino.shape.type;
            }
        }
    }
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        bool completed = true;
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (field[y][x] == 0) {
                completed = false;  break;
            }
        }
        if (completed) {
            *score += 100;
            for (int x = 0; x < FIELD_WIDTH; x++) {
                field[y][x] = 0;
            }
            for (int y2 = y; y2 > 1; y2--) {
                for (int x = 0; x < FIELD_WIDTH; x++) {
                    field[y2][x] = field[y2 - 1][x];
                    field[y2 - 1][x] = 0;
                }
            }
        }
    }
    for (int x = 0; x < FIELD_WIDTH; x++) {
        if (field[0][x] != 0) {
            return 1;
        }
    }
    hold_status = hold_status == 0 ? 0 : 1;
    *next = InitMino(*next);
    return 0;
}

void DrawExplanation() {
    mvprintw(13 + Y, 26 + X, "→　：　右移動");
    mvprintw(14 + Y, 26 + X, "←　：　左移動");
    mvprintw(15 + Y, 26 + X, "↓　：　下移動");
    mvprintw(16 + Y, 26 + X, "↑　：　回転");
    mvprintw(17 + Y, 26 + X, "他　：　保留");
}

int GameRun() {
    int next = Init();
    int score = 0;
    clock_t lastClock = clock();
    int isFinished = 0;
    int intervel = 1000;
    int level = 1;
    while (1) {
        clear();
        DrawScrean();
        //DrawField();
        DrawExplanation();
        clock_t nowClock = clock();
        if (nowClock - lastClock >= intervel) {
            lastClock = nowClock;
            MINO lastMino = mino;
            mino.y++;
            if (MinoIntercectField()) {
                mino = lastMino;
                isFinished = CompleteFlow(&next, &score);
            }
            DrawScrean();
        }
        if (isFinished) break;
        DrawNextMino(next);
        DrawHoldMino(hold_status);
        level = score / 500 + 1;
        intervel = 1000 / level;
        mvprintw(9 + Y, 26 + X, "score: %d", score);
        mvprintw(10 + Y, 26 + X, "level: %d", level);
        MINO lastMino = mino;
        if (_kbhit()) {
            int key = getch();
            KeyAction(key, &next);
        }
        if (MinoIntercectField()) {
            mino = lastMino;
        }
        refresh();
    }
    endwin();
    return score;
}
