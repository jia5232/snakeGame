#include "SnakeMap.h"
#include "Snake.h"
#include "ItemGenerator.h"
#include "Gate.h"
#include <vector>
#include <ncurses.h>
#include <thread>
#include <iostream>

using namespace std;

#define ITEM_REGEN 50
#define GAME_OVER -1
#define GAME_CONTINUE 1
#define GAME_STAGE_CLEAR 2
#define GAME_ALL_CLEAR 3

#define FREE_SPACE 0
#define WALL 1
#define IMMNUME_WALL 2
#define SNAKE_HEAD 3
#define SNAKE_BODY 4
#define GROWTH_ITEM 5
#define POSION_ITEM 6
#define GATE 7

SnakeMap::SnakeMap(WINDOW *mainWin, int height, int width) : mainWin(mainWin), mapWidth(width), mapHeight(height)
{
    stage = Stage();
    stage.drawInitStage(mainWin); //현재 어떤 스테이지인지 게임 시작전에 알려줌.
    std::this_thread::sleep_for(std::chrono::seconds(2)); //화면 2초간 고정

    mapArray = new int *[mapHeight];
    for (int i = 0; i < mapHeight; i++)
    {
        mapArray[i] = new int[mapHeight];
    }

    this->initMap(stage.getNextStage());
    gate = Gate();
    gate.generateRandomGate(mapArray);
}
void SnakeMap::initMap(vector<vector<int>> obstacles){ //스테이지에서 설정한 obstacle을 받아서 맵을 초기화.
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapHeight; j++){
            if((i != 0 && i != 20) && (j != 0 && j != 20)){
                mapArray[i][j] = obstacles[i][j];
            }else{ //가장자리는 값이 고정되므로 따로 처리
                if((i == 0 && j == 0) || (i == 0 && j == 20) || (i == 20 && j == 0) || (i == 20 && j == 20)){
                    mapArray[i][j] = 2;
                }
                else
                {
                    mapArray[i][j] = 1;
                }
            }
        }
    }
}

int SnakeMap::drawSnakeMap(Snake &sk, ItemGenerator &growth, ItemGenerator &poison)
{
    vector<SnakeVector> sv = sk.getSnake();
    bool isGrowth = false;
    bool isPoison = false;
    ItemCoordinate growthCor = growth.getItemCoordinate();
    ItemCoordinate poisonCor = poison.getItemCoordinate();
    mapArray[growthCor.row][growthCor.col] = 5;
    mapArray[poisonCor.row][poisonCor.col] = 6;

    bool isGate = gate.getIsGate();
    GateCoordinate gate1 = gate.getGate(1);
    GateCoordinate gate2 = gate.getGate(2);

    if (sv.size() < 3)
    {
        return GAME_OVER;
    }
    for (int i = 0; i < sv.size(); i++)
    {
        int row = sv[i].row;
        int col = sv[i].col;
        // 스네이크가 1(벽)에 접근시 리턴 -1
        if (mapArray[row][col] == 1)
        {
            return GAME_OVER;
        }
        if (i == 0)
        {
            if (mapArray[row][col] == GROWTH_ITEM)
            {
                isGrowth = true;
                stage.addGrowth();
            }
            else if (mapArray[row][col] == POSION_ITEM)
            {
                isPoison = true;
                stage.addPoison();
            }
            else if (mapArray[row][col] == GATE)
            {
                gate.setIsGate(true);
                if (row == gate1.row && col == gate1.col)
                { // gate1로 진입 시
                    gate.setOption(1);
                    gate.setSnake(gate2, sk, mapArray); // gate2를 이용해 방향 스네이크 헤드 위치 및 방향 변경
                }
                else if (row == gate2.row && col == gate2.col)
                { // gate2로 진입 시
                    gate.setOption(2);
                    gate.setSnake(gate1, sk, mapArray); // gate1을 이용해 방향 스네이크 헤드 위치 및 방향 변경
                }
                stage.passGate();
            }
            // mapArray[row][col] = 3;
            mapArray[sv[i].row][sv[i].col] = SNAKE_HEAD;
        }
        else
        {
            // 스네이크 헤드와 바디의 좌표가 겹칠 때 리턴 GAME_OVER
            if (row == sv[0].row && col == sv[0].col)
            {
                return GAME_OVER;
            }
            mapArray[row][col] = SNAKE_BODY;
        }
    }

    // Gate
    if (gate.getGateTimer() <= 0)
    {
        mapArray[gate1.row][gate1.col] = GATE;
        mapArray[gate2.row][gate2.col] = GATE;
    }

    // isGate가 true일 때 Gate에 들어가있는 상태
    if (isGate)
    {
        if (gate.getOption() == 1)
        {                                        // gate1로 들어간 경우
            gate.checkGatePassed(sk, sv, gate2); // gate2를 빠져나왔는지 확인
        }
        else if (gate.getOption() == 2)
        {                                        // gate2로 들어간 경우
            gate.checkGatePassed(sk, sv, gate1); // gate1을 빠져나왔는지 확인
        }

        if (!gate.getIsGate())
        { // Gate를 빠져나와서 isGate가 false가 되면
            // 기존 Gate를 맵에서 지워줌
            mapArray[gate1.row][gate1.col] = 1;
            mapArray[gate2.row][gate2.col] = 1;
            gate.generateRandomGate(mapArray);
        }
    }

    //위에서는 데이터를 업데이트하고, 이제 화면에 업데이트해줌.
    stage.drawCurrentStage();
    stage.drawScoreBoard(); //현재 스코어를 알려주는 보드
    stage.drawMission(); //목표치를 알려주는 보드

    for (int i = 0; i < mapHeight; i++)
    {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);

        for (int j = 0; j < mapWidth; j++)
        {
            if (j % 2 != 0)
            {
                mvwprintw(mainWin, i, j, " ");
            }
            else
            {
                if (mapArray[i][j / 2] == FREE_SPACE)
                {
                    mvwprintw(mainWin, i, j, "-");
                }
                else if (mapArray[i][j / 2] == WALL)
                {
                    mvwprintw(mainWin, i, j, "#");
                }
                else if (mapArray[i][j / 2] == IMMNUME_WALL)
                {
                    mvwprintw(mainWin, i, j, "+");
                }
                else if (mapArray[i][j / 2] == SNAKE_HEAD)
                {
                    mvwprintw(mainWin, i, j, "^");
                }
                else if (mapArray[i][j / 2] == SNAKE_BODY)
                {
                    mvwprintw(mainWin, i, j, "@");
                }
                else if (mapArray[i][j / 2] == GROWTH_ITEM)
                {
                    wattron(mainWin, COLOR_PAIR(1));
                    mvwprintw(mainWin, i, j, "$");
                    wattroff(mainWin, COLOR_PAIR(1));
                }
                else if (mapArray[i][j / 2] == POSION_ITEM)
                {
                    wattron(mainWin, COLOR_PAIR(2));
                    mvwprintw(mainWin, i, j, "P");
                    wattroff(mainWin, COLOR_PAIR(2));
                }
                else if (mapArray[i][j / 2] == GATE)
                {
                    wattron(mainWin, COLOR_PAIR(3));
                    mvwprintw(mainWin, i, j, "G");
                    wattroff(mainWin, COLOR_PAIR(3));
                }
            }
        }
    }

    sk.snakeMove();
    if (isPoison)
    {
        SnakeVector skPop = sk.popSnake();
        mapArray[skPop.row][skPop.col] = 0;
        skPop = sk.popSnake();
        mapArray[skPop.row][skPop.col] = 0;
    }
    else if (!isGrowth)
    {
        SnakeVector skPop = sk.popSnake();
        mapArray[skPop.row][skPop.col] = 0;
    }
    
    if(stage.isMissionClear()){ //미션이 클리어되면,
        if(stage.goNextStage()){ //마지막 스테이지가 아니라면 다음 스테이지로 이동하기 위한 설정 초기화.
            this->initMap(stage.getNextStage()); //다음 스테이지의 맵(obstacle)으로 초기화
            gate.generateRandomGate(mapArray); 
            gate.setGateTimer(50);
            stage.drawInitStage(mainWin); //다음 스테이지 번호를 알려줌.
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return GAME_STAGE_CLEAR;
        }
        clear();
        return GAME_ALL_CLEAR; //마지막 스테이지라면 GAME_ALL_CLEAR 반환하고 게임을 끝냄.
    }

    if (growth.getItemTimer() >= ITEM_REGEN)
    {
        mapArray[growthCor.row][growthCor.col] = 0;
        ItemCoordinate growthCor = growth.generateRandomItem(mapArray, mapHeight - 2);
        mapArray[growthCor.row][growthCor.col] = 5;
    }
    else if (isGrowth)
    {
        ItemCoordinate growthCor = growth.generateRandomItem(mapArray, mapHeight - 2);
        mapArray[growthCor.row][growthCor.col] = 5;
    }
    if (poison.getItemTimer() >= ITEM_REGEN)
    {
        mapArray[poisonCor.row][poisonCor.col] = 0;
        ItemCoordinate poisonCor = poison.generateRandomItem(mapArray, mapHeight - 2);
        mapArray[poisonCor.row][poisonCor.col] = 6;
    }
    else if (isPoison)
    {
        ItemCoordinate poisonCor = poison.generateRandomItem(mapArray, mapHeight - 2);
        mapArray[poisonCor.row][poisonCor.col] = 6;
    }

    return GAME_CONTINUE;
}
