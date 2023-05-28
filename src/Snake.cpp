#include "Snake.h"
#include <ncurses.h>
// #include <iostream>
// using namespace std;
Snake::Snake(int len, int direction, int row, int col){
    snakeLen = len;
    snakeDirection = direction;
    if(col % 2 != 0){
        snakeHeadCol = col / 2 - 1;
    }else{
        snakeHeadCol = col / 2;
    }
    snakeHeadRow = row / 2;
    
    mapRow = row;
    mapCol = col;
    for(int i = 0; i < len; i++){
        snake.push_back({snakeHeadRow - i, snakeHeadCol});
    }
    //헤드 위치 설정해야함
}
int Snake::getSnakeLen()const{
    return snakeLen;
}
// int Snake::getSnakeDirection()const{
//     return snakeDirection;
// }
void Snake::setSnakeDirection(int direction){
    snakeDirection = direction;
}
// void Snake::setSnakeLen(int len){
//     snakeLen = len;
// }
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
        headCol+=2;
    } else if (snakeDirection == KEY_LEFT) {
        headCol-=2;
    } else if (snakeDirection == KEY_UP) {
        headRow--;
    } else if (snakeDirection == KEY_DOWN) {
        headRow++;
    }

    // 머리 이동 후 경계 처리
    if (headRow < 0)
        headRow = mapRow - 1;
    else if (headRow >= mapRow)
        headRow = 0;
    if (headCol < 0)
        headCol = mapCol - 1;
    else if (headCol >= mapCol)
        headCol = 0;

    // 머리 위치 업데이트
    snakeHeadRow = headRow;
    snakeHeadCol = headCol;

    // 머리 추가
    snake.insert(snake.begin(), {snakeHeadRow, snakeHeadCol});

    // 꼬리 제거
    snake.pop_back();

    // 게임 화면 업데이트
    for (int i = 0; i < snakeLen; i++) {
        mvprintw(snake[i].row, snake[i].col, "O");
    }
}

// int main(){
//     Snake sk(3, 1);
//     cout << sk.getSnakeDirection() << endl;
//     cout << sk.getSnakeLen() << endl;
//     sk.setSnakeDirection(1);
//     sk.setSnakeLen(4);
//     cout << sk.getSnakeDirection() << endl;
//     cout << sk.getSnakeLen() << endl;
//     sk.setSnakeHeadPosition(4,5);
// }
