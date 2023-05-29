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
int Snake::getSnakeLen()const{
    return snakeLen;
}
void Snake::setSnakeLen(int len){
    snakeLen = len;
}
void Snake::setSnakeDirection(int direction){
    snakeDirection = direction;
}
//뱀 좌표를 전달하는 함수
vector<SnakeVector> Snake::getSnake() const {
    return snake;
}
void Snake::popSnake()  {
    snake.pop_back();
}
void Snake::setSnakeHeadPosition(int row, int col){
    snakeHeadRow = row;
    snakeHeadCol = col;
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
    // 머리 이동 후 경계 처리
    // if (headRow < 0)
    //     headRow = mapHeight - 1;
    // else if (headRow >= mapHeight)
    //     headRow = 0;
    // if (headCol < 0)
    //     headCol = mapWidth - 1;
    // else if (headCol >= mapWidth)
    //     headCol = 0;
    // 머리 위치 업데이트
    snakeHeadRow = headRow;
    snakeHeadCol = headCol;
    // //경계선에 닿으면 죽음
    // if(snakeHeadRow == 0 || snakeHeadCol == 0 || snakeHeadRow == mapHeight - 1 || snakeHeadCol == mapWidth - 1){
    //     return true;
    // }
    // 머리 추가
    snake.insert(snake.begin(), {snakeHeadRow, snakeHeadCol});
    // 꼬리 제거
    snake.pop_back();
}