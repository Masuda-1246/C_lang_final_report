#include <conio.h>
#include <curses.h>
#include <Windows.h>

void newName(char* name) {
    initscr();
    cbreak();
    noecho();
    printw("Please enter your name: ");
    refresh();
    getnstr(name, sizeof(name));
    printw("\nHello, %s! Nice to meet you.", name);
    printw("\nPlease press enter. You can start game! ");
    refresh();
    getch();
    endwin();
}