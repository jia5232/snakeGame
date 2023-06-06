#ifndef GATEGENERATOR_H
#define GATEGENERATOR_H

#include "Snake.h"

struct GateCoordinate{
    int row, col;
    int location; // 가장자리 벽 or 중앙 벽
};

class Gate{
    private:
    GateCoordinate gate1;
    GateCoordinate gate2;
    int gateTimer;
    bool isGate;
    int option;
    public:
    Gate(int **mapArray);
    GateCoordinate getGate(int gateNum);
    // GateCoordinate getGate2();
    void generateRandomGate(int **mapArray);
    int getGateTimer();
    void setGateTimer(int num);
    bool getIsGate();
    void setIsGate(bool state);
    int getOption();
    void setOption(int num);
    void isGateLocation(GateCoordinate& gate);
    int getGateLocation(GateCoordinate& gate);
    void setSnake(GateCoordinate& gate, Snake& snake, int **mapArray); // gate의 location을 가지고 스네이크의 위치 및 방향 설정
    void edgeGate(int gateRow, int gateCol, Snake& snake);
    void centerGate(int gateRow, int gateCol, Snake& snake, int **mapArray);
    void checkGatePassed(Snake sk, vector<SnakeVector> sv, GateCoordinate gate);
};
#endif