#ifndef SnakeMap_H
#define SnakeMap_H
#include <iostream>
#include <ncurses.h>
#include "Snake.h"
#include "ItemGenerator.h"
#include "GateGenerator.h"
using namespace std;
class SnakeMap {
private:
    WINDOW* mainWin;
    int **mapArray;
    int mapWidth;
    int mapHeight;

public:
    SnakeMap(WINDOW* mainWin,int **map, int height, int width);
    int drawSnakeMap(Snake& sk, int direction, ItemGenerator& growth, ItemGenerator& poison, GateGenerator& gate);
    void mapReset();
};

#endif
