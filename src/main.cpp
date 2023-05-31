#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include "Snake.h"
#include "SnakeMap.h"
#include "ItemGenerator.h"
#include "GateGenerator.h"

using namespace std;
#define TICK_RATE 150

int main()
{
    int MAP_HEIGHT = 21;
    int MAP_WIDTH = 41;
    int mainWinRow = 5;
    int mainWinCol = 5;
    
    initscr();
    resize_term(300, 300);
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    int direction = KEY_DOWN;
    WINDOW *mainWindow = newwin(MAP_HEIGHT, MAP_WIDTH, mainWinRow, mainWinCol);
    int mapTemp[][21] = {{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}};
    int **mapTempPtr = new int *[21];
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        mapTempPtr[i] = mapTemp[i];
    }

    SnakeMap sMap(mainWindow, mapTempPtr, MAP_HEIGHT, MAP_WIDTH);
    Snake sk(MAP_HEIGHT, 3);
    ItemGenerator growth(5, 5);
    ItemGenerator poison(2, 2);
    GateGenerator gate(mapTempPtr);

    bool quit = false;
    bool die = false;
    // 틱 간격 설정
    constexpr chrono::milliseconds tickDuration(TICK_RATE); // 200 밀리초 (0.2초)
    while (!quit)
    {
        // 키 입력 처리
        int key = getch();

        switch (key)
        {
        case KEY_UP:
            if (direction != KEY_DOWN) // 반대 방향으로는 이동할 수 없도록 처리
                direction = KEY_UP;
            break;
        case KEY_DOWN:
            if (direction != KEY_UP)
                direction = KEY_DOWN;
            break;
        case KEY_LEFT:
            if (direction != KEY_RIGHT)
                direction = KEY_LEFT;
            break;
        case KEY_RIGHT:
            if (direction != KEY_LEFT)
                direction = KEY_RIGHT;
            break;
        case 'q':
            quit = true;
            break;
        }

        // 게임 화면 업데이트
        clear();
        int gameState = sMap.drawSnakeMap(sk, direction, growth, poison, gate);
        if (gameState == -1){
            clear();
            mvwprintw(mainWindow,10, 10, "Game Over!");
            wrefresh(mainWindow);
            break;
        }
        wrefresh(mainWindow);

        // 틱 간격 지연
        this_thread::sleep_for(tickDuration);
    }
}