#include "Snake.h"
#include <ncurses.h>
#include <iostream>
// using namespace std;
Snake::Snake(int mapHeight, int len)
:snakeLen(len), mapHeight(mapHeight)
{
    snakeHeadCol = mapHeight / 2;
    
    snakeHeadRow = mapHeight / 2;
    for(int i = 0; i < len; i++){
        snake.push_back({snakeHeadRow - i, snakeHeadCol});
    }
    //헤드 위치 설정해야함
}
// int Snake::getSnakeLen()const{
//     return snakeLen;
// }
// void Snake::setSnakeLen(int len){
//     snakeLen = len;
// }
void Snake::setSnakeDirection(int direction){
    snakeDirection = direction;
}
//뱀 좌표를 전달하는 함수
vector<SnakeVector> Snake::getSnake() const {
    return snake;
}
SnakeVector Snake::popSnake()  {
    SnakeVector temp = snake.back();
    snake.pop_back();
    return temp;
}
void Snake::snakeMove(int direction){
    snakeDirection = direction;
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