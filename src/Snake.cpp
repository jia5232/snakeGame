#include "Snake.h"
#include <ncurses.h>
#include <iostream>
// using namespace std;
Snake::Snake(int mapHeight, int len, int direction)
:snakeLen(len), mapHeight(mapHeight), snakeDirection(direction)
{
    snakeHeadCol = mapHeight / 2;
    
    snakeHeadRow = mapHeight / 2;
    for(int i = 0; i < len; i++){
        snake.push_back({snakeHeadRow - i, snakeHeadCol});
    }
}
// int Snake::getSnakeLen()const{
//     return snakeLen;
// }
// void Snake::setSnakeLen(int len){
//     snakeLen = len;
// }
//뱀 좌표를 전달하는 함수
vector<SnakeVector> Snake::getSnake() const {
    return snake;
}
SnakeVector Snake::popSnake()  {
    SnakeVector temp = snake.back();
    snake.pop_back();
    return temp;
}
void Snake::setSnakeDirection(int direction){
    snakeDirection = direction;
}
int Snake::getSnakeDirection() const{
    return snakeDirection;
}
void Snake::setSnakeHead(int row, int col){
    snakeHeadRow = row;
    snakeHeadCol = col;
    snake[0].row = row;
    snake[0].col = col;
}
void Snake::snakeMove(){
    // 현재 머리 위치
    int headRow = snakeHeadRow;
    int headCol = snakeHeadCol;
    
    if (snakeDirection == KEY_RIGHT) {
        headCol++;
    } else if (snakeDirection == KEY_LEFT) {
        headCol--;
    } else if (snakeDirection == KEY_UP) {
        headRow--;
    } else if (snakeDirection == KEY_DOWN) {
        headRow++;
    }

    snakeHeadRow = headRow;
    snakeHeadCol = headCol;
    // 머리 추가
    snake.insert(snake.begin(), {snakeHeadRow, snakeHeadCol});
}