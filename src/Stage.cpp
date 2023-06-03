#include "Stage.h"
#include <iostream>
#include <ncurses.h>

using namespace std;

int missionValues[4][4] = {{5,1,0,0},{7,2,1,0},{8,3,1,1},{10,5,2,2}};

Stage::Stage(){}
Stage::Stage(WINDOW* mainWin){
    this->mainWin = mainWin;
    maxStageNumber = 4;
    currentStage = 1;

    scoreBoard.snakeLength = 3;
    scoreBoard.growth = 0;
    scoreBoard.poison = 0;
    scoreBoard.gateCount = 0;
    for(int i = 0; i < 4; i++){
       Mission mission(missionValues[i][0],missionValues[i][1],missionValues[i][2],missionValues[i][3]);
       missions.push_back(mission); 
    }
}

void Stage::drawCurrentStage(){
    cout << "Stage"<< currentStage << "\n\r";
}

bool Stage::goNextStage(){
    currentStage++;
    if(currentStage == maxStageNumber){
        return false;
    }
    scoreBoard.snakeLength = 3;
    scoreBoard.growth = 0;
    scoreBoard.poison = 0;
    scoreBoard.gateCount = 0;
    return true;
}

void Stage::printBanner(string title, string B, int growth, int poison, int gate){
    
    cout << "*****************************\n\r";
    cout << "[" << title << "]\n\r";
    cout << "B: " << B << "\n\r";
    cout << "+: "<< growth << "\n\r";
    cout << "-: " << poison << "\n\r";
    cout << "G: " << gate << "\n\r";
    cout << "*****************************" << "\n\r\n\r";
}

void Stage::drawScoreBoard(){
    Mission currMission = missions[currentStage - 1];
    string B = to_string(scoreBoard.snakeLength) + " / "  + to_string(currMission.achievement);
    printBanner("Score board", B, scoreBoard.growth, scoreBoard.poison, scoreBoard.gateCount);
}

void Stage::drawMission(){
    Mission currMission = missions[currentStage - 1];
    string B = to_string(currMission.achievement);
    printBanner("Mission", B, currMission.growth, currMission.poison, currMission.gateCount);
}

bool Stage::isMissionClear(){
    Mission currMission = missions[currentStage - 1];
    if(scoreBoard.snakeLength >= currMission.achievement &&
        scoreBoard.growth >= currMission.growth &&
        scoreBoard.poison >= currMission.poison &&
        scoreBoard.gateCount >= currMission.gateCount){
        return true;
    }
    return false;
}

void Stage::addGrowth(){
    scoreBoard.growth++;
    scoreBoard.snakeLength++;
}

void Stage::addPoison(){
    scoreBoard.poison++;
    scoreBoard.snakeLength--;
}

void Stage::passGate(){
    scoreBoard.gateCount++;
}