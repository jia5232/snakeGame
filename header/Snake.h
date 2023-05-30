#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <ncurses.h>
#include "Snake.h"
using namespace std;
struct SnakeVector
{
    int row, col;
};
class Snake
{

private:
    vector<SnakeVector> snake;
    WINDOW *mainWin;
    int snakeLen;
    int snakeDirection;
    int snakeHeadRow;
    int snakeHeadCol;
    int mapWidth, mapHeight;

public:
    Snake(int mapHeight, int len);
    void setSnakeDirection(int direction);
    SnakeVector popSnake() ;
    void snakeMove(int direction);
    vector<SnakeVector> getSnake() const;
    // int getSnakeLen() const;
    // void setSnakeLen(int len);
};

#endif