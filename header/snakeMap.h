#ifndef SnakeMap_H
#define SnakeMap_H
#include <iostream>
#include <ncurses.h>
#include "Snake.h"
using namespace std;
class SnakeMap {
private:
    WINDOW* mainWin;
    int **mapArray;
    int mapWidth;
    int mapHeight;
public:
    SnakeMap(WINDOW* mainWin,int **map, int height, int width);
    void drawSnakeMap(Snake& sk, int direction);
    void mapReset();
};

#endif
