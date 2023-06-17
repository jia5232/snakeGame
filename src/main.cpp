#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include "Snake.h"
#include "SnakeMap.h"
#include "ItemGenerator.h"
#include "Gate.h"

using namespace std;
#define TICK_RATE 150

int main()
{
    int MAP_HEIGHT = 21;
    int MAP_WIDTH = 41;
    int mainWinRow = 3;
    int mainWinCol = 5;

    initscr();
    start_color();
    resize_term(300, 300);
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    int direction = KEY_DOWN;
    WINDOW *mainWindow = newwin(MAP_HEIGHT, MAP_WIDTH, mainWinRow, mainWinCol);

    SnakeMap sMap(mainWindow, MAP_HEIGHT, MAP_WIDTH);
    Snake sk(MAP_HEIGHT, 3, direction);
    ItemGenerator growth(5, 5);
    ItemGenerator poison(2, 2);
    // Gate gate(mapTempPtr);

    bool quit = false;
    // 틱 간격 설정
    constexpr chrono::milliseconds tickDuration(TICK_RATE); // 200 밀리초 (0.2초)
    while (!quit)
    {
        // 키 입력 처리
        int key = getch();

        switch (key)
        {
        case KEY_UP:
            if (sk.getSnakeDirection() == KEY_DOWN)
            {
                clear();
                mvwprintw(mainWindow, 10, 10, "Game Over!");
                wrefresh(mainWindow);
                break;
            } // 반대 방향으로는 이동하면 gamover
            sk.setSnakeDirection(KEY_UP);
            break;
        case KEY_DOWN:
            if (sk.getSnakeDirection() == KEY_UP){
                clear();
                mvwprintw(mainWindow, 10, 10, "Game Over!");
                wrefresh(mainWindow);
            } // 반대 방향으로는 이동하면 gamover
            sk.setSnakeDirection(KEY_DOWN);
                
            break;
        case KEY_LEFT:
            if (sk.getSnakeDirection() == KEY_RIGHT){
                clear();
                mvwprintw(mainWindow, 10, 10, "Game Over!");
                wrefresh(mainWindow);
            } // 반대 방향으로는 이동하면 gamover
            sk.setSnakeDirection(KEY_LEFT);
            break;
        case KEY_RIGHT:
            if (sk.getSnakeDirection() == KEY_LEFT){
                clear();
                mvwprintw(mainWindow, 10, 10, "Game Over!");
                wrefresh(mainWindow);
            } // 반대 방향으로는 이동하면 gamover
            sk.setSnakeDirection(KEY_RIGHT);
            break;
        case 'q':
            quit = true;
            break;
        }

        // 게임 화면 업데이트
        clear();
        int gameState = sMap.drawSnakeMap(sk, growth, poison);

        if (gameState == -1)
        {
            clear();
            mvwprintw(mainWindow, 10, 10, "Game Over!");
            wrefresh(mainWindow);
            break;
        }
        else if (gameState == 2)
        { // go to next stage
            clear();
            sk = Snake(MAP_HEIGHT, 3, direction);
            growth = ItemGenerator(5, 5);
            poison = ItemGenerator(2, 2);
        }
        else if (gameState == 3)
        {
            clear();
            mvwprintw(mainWindow, 0, 0, "All Clear!");
            wrefresh(mainWindow);
            break;
        }
        wrefresh(mainWindow);

        // 틱 간격 지연
        this_thread::sleep_for(tickDuration);
    }
}