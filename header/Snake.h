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
    int getSnakeLen() const;
    void setSnakeDirection(int direction);
    void setSnakeLen(int len);
    void setSnakeHeadPosition(int row, int col);
    void pushSnake();
    void popSnake() ;
    void snakeMove(int direction);
    vector<SnakeVector> getSnake() const;
};

#endif