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

public:
    SnakeMap(WINDOW* mainWin,int **map, int height, int width);
    int drawSnakeMap(Snake& sk, ItemGenerator& growth, ItemGenerator& poison, Gate& gate);
    void initMap(vector<vector<int>> obstacles);
};

#endif
