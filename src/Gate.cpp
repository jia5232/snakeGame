#include "Gate.h"
#include <iostream>
#include <random>
using namespace std;

Gate::Gate(){
    // generateRandomGate(mapArray);
    isGate = false;
    gateTimer = 50;
    option = 0;
}

void Gate::generateRandomGate(int **mapArray)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> randomNum(0, 20);

    bool retry = false;

    do{
        retry = false;

        gate1.row = randomNum(gen);
        gate1.col = randomNum(gen);
        gate2.row = randomNum(gen);
        gate2.col = randomNum(gen);

        if(mapArray[gate1.row][gate1.col] != 1 || mapArray[gate2.row][gate2.col] != 1){
            retry = true;
        }
        if(gate1.row == gate2.row && gate1.col == gate2.col){
            retry = true;
        }
    } while (retry);

    isGateLocation(gate1);
    isGateLocation(gate2);

    // gateTimer = 50;
}

GateCoordinate Gate::getGate(int gateNum){
    gateTimer--;
    if (gateNum == 1){
        return gate1;
    }else {
        return gate2;
    }
}

int Gate::getGateTimer(){
    return gateTimer;
}

void Gate::setGateTimer(int num){
    gateTimer = num;
}

bool Gate::getIsGate(){
    return isGate;
}

void Gate::setIsGate(bool state){
    isGate = state;
}

int Gate::getOption(){
    return option;
}

void Gate::setOption(int num){
    option = num;
}

void Gate::isGateLocation(GateCoordinate& gate){
    if(gate.row == 0 || gate.col == 0 || gate.row == 20 || gate.col == 20){
        gate.location = 0; // 가장자리 벽 게이트
    }else{ 
        gate.location = 1; // 중앙 벽 게이트
    }
}

int Gate::getGateLocation(GateCoordinate& gate){
    return gate.location;
}

void Gate::setSnake(GateCoordinate& gate, Snake& snake, int **mapArray){
    if(gate.location == 0){
        edgeGate(gate.row, gate.col, snake);
    }
    else if(gate.location == 1){
        centerGate(gate.row, gate.col, snake, mapArray);
    }
}

void Gate::edgeGate(int gateRow, int gateCol, Snake& snake){
    if(gateRow == 0){
        snake.setSnakeDirection(KEY_DOWN);
        snake.setSnakeHead(gateRow + 1, gateCol);
    }else if(gateRow == 20){
        snake.setSnakeDirection(KEY_UP);
        snake.setSnakeHead(gateRow - 1, gateCol);
    }else if(gateCol == 0){
        snake.setSnakeDirection(KEY_RIGHT);
        snake.setSnakeHead(gateRow, gateCol + 1);
    }else if(gateCol == 20){
        snake.setSnakeDirection(KEY_LEFT);
        snake.setSnakeHead(gateRow, gateCol - 1);
    }
}

void Gate::centerGate(int gateRow, int gateCol, Snake& snake, int **mapArray){
    int dir = snake.getSnakeDirection();

    int down = gateRow + 1; // 아랫쪽 방향 
    int up = gateRow - 1; // 위쪽 방향
    int right = gateCol + 1; // 오른쪽 방향
    int left = gateCol - 1; // 왼쪽 방향

    // 시계 방향 체크
    if(dir == KEY_UP){
        if(mapArray[up][gateCol] == 0){ // 위
            snake.setSnakeDirection(KEY_UP);
            snake.setSnakeHead(up, gateCol);
        }else if(mapArray[gateRow][right] == 0){ // 오
            snake.setSnakeDirection(KEY_RIGHT);
            snake.setSnakeHead(gateRow, right);
        }else if(mapArray[gateRow][left] == 0){ // 왼
            snake.setSnakeDirection(KEY_LEFT);
            snake.setSnakeHead(gateRow, left);
        }else if(mapArray[down][gateCol] == 0){ // 아
            snake.setSnakeDirection(KEY_DOWN);
            snake.setSnakeHead(down, gateCol);
        }
    }
    else if (dir == KEY_RIGHT){
        if(mapArray[gateRow][right] == 0){ // 오
            snake.setSnakeDirection(KEY_RIGHT);
            snake.setSnakeHead(gateRow, right);
        }else if(mapArray[down][gateCol] == 0){ // 아
            snake.setSnakeDirection(KEY_DOWN);
            snake.setSnakeHead(down, gateCol);
        }else if(mapArray[up][gateCol] == 0){ // 위
            snake.setSnakeDirection(KEY_UP);
            snake.setSnakeHead(up, gateCol);
        }else if(mapArray[gateRow][left] == 0){ // 왼
            snake.setSnakeDirection(KEY_LEFT);
            snake.setSnakeHead(gateRow, left);
        }
    }
    else if (dir == KEY_DOWN){
        if(mapArray[down][gateCol] == 0){ // 아
            snake.setSnakeDirection(KEY_DOWN);
            snake.setSnakeHead(down, gateCol);
        }else if(mapArray[gateRow][left] == 0){ // 왼
            snake.setSnakeDirection(KEY_LEFT);
            snake.setSnakeHead(gateRow, left);
        }else if(mapArray[gateRow][right] == 0){ // 오
            snake.setSnakeDirection(KEY_RIGHT);
            snake.setSnakeHead(gateRow, right);
        }else if(mapArray[up][gateCol] == 0){ // 위
            snake.setSnakeDirection(KEY_UP);
            snake.setSnakeHead(up, gateCol);
        }
    }
    else if (dir == KEY_LEFT){
        if(mapArray[gateRow][left] == 0){ // 왼
            snake.setSnakeDirection(KEY_LEFT);
            snake.setSnakeHead(gateRow, left);
        }else if(mapArray[up][gateCol] == 0){ // 위
            snake.setSnakeDirection(KEY_UP);
            snake.setSnakeHead(up, gateCol);
        }else if(mapArray[down][gateCol] == 0){ // 아
            snake.setSnakeDirection(KEY_DOWN);
            snake.setSnakeHead(down, gateCol);
        }else if(mapArray[gateRow][right] == 0){ // 오
            snake.setSnakeDirection(KEY_RIGHT);
            snake.setSnakeHead(gateRow, right);
        }
    }
}

void Gate::checkGatePassed(Snake sk, vector<SnakeVector > sv, GateCoordinate gate){
    int len = sv.size() - 1;
    int dir = sk.getSnakeDirection();

    int down = gate.row + 1; 
    int up = gate.row - 1; 
    int right = gate.col + 1; 
    int left = gate.col - 1; 

    if(dir == KEY_DOWN){
        if (sv[len].row == down && sv[len].col == gate.col){
            isGate = false;
        }else{
            isGate = true;
        }
    }else if(dir == KEY_UP){
        if (sv[len].row == up && sv[len].col == gate.col){
            isGate = false;
        }else{
            isGate = true;
        }
    }else if(dir == KEY_LEFT){
        if (sv[len].row == gate.row && sv[len].col == left){
            isGate = false;
        }else{
            isGate = true;
        }
    }else if(dir == KEY_RIGHT){
        if (sv[len].row == gate.row && sv[len].col == right){
            isGate = false;
        }else{
            isGate = true;
        }
    }
}