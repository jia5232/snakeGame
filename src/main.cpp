#include <iostream>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include "Snake.h"
#include "SnakeMap.h"
using namespace std;

int main()
{
    int BOARD_ROW = 21;
    int BOARD_COL = 43;
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    int direction = KEY_RIGHT;

    SnakeMap sMap(BOARD_ROW, BOARD_COL);
    Snake sk(3, direction, BOARD_ROW, BOARD_COL);

    bool quit = false;
    // 틱 간격 설정
    constexpr chrono::milliseconds tickDuration(100); // 200 밀리초 (0.2초)
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
        for (int i = 0; i < BOARD_ROW; i++)
        {
            for (int j = 0; j < BOARD_COL; j++)
            {
                if (j % 2 == 0)
                {
                    mvprintw(i, j, "%c", sMap.mapArray[i][j]);
                }
                else
                {
                    mvprintw(i, j, " ");
                }
                
            }
        }
        sk.snakeMove(direction);

        refresh();

        // 틱 간격 지연
        this_thread::sleep_for(tickDuration);
    }
}