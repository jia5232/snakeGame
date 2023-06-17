#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <ncurses.h>
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
    Snake(int mapHeight, int len, int direction);
    SnakeVector popSnake() ;
    void snakeMove();
    vector<SnakeVector> getSnake() const;
    void setSnakeDirection(int direction);
    int getSnakeDirection() const;
    void setSnakeHead(int row, int col);
};

#endif