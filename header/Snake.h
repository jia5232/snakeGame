#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
using namespace std;
class Snake{
    struct SnakeVector{
        int row, col;
    };
    private:
    vector<SnakeVector> snake;
    int snakeLen;
    int snakeDirection;
    int snakeHeadRow;
    int snakeHeadCol;
    int mapRow, mapCol;
    public:
    
    Snake(int len = 3, int direction = 1, int row = 0, int col = 0);
    // Snake(const char *snakeArray);
    int getSnakeLen() const;
    // int getSnakeDirection() const;
    void setSnakeDirection(int direction);
    // void setSnakeLen(int len);
    void setSnakeHeadPosition(int row, int col);
    void pushSnake();
    void popSnake();
    void snakeMove(int direction);
};

#endif