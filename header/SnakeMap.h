#ifndef SnakeMap_H
#define SnakeMap_H
#include <iostream>
#include <ncurses.h>
#include "Snake.h"
#include "ItemGenerator.h"
#include "Gate.h"
#include "Stage.h"
using namespace std;
class SnakeMap {
private:
    WINDOW* mainWin;
    int **mapArray;
    int mapWidth;
    int mapHeight;
    Stage stage;
    Gate gate;

public:
    SnakeMap(WINDOW* mainWin, int height, int width);
    int drawSnakeMap(Snake& sk, ItemGenerator& growth, ItemGenerator& poison);
    void initMap(vector<vector<int>> obstacles);
};

#endif
