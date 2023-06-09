#ifndef STAGE_H
#define STAGE_H
#include <vector>
#include <ncurses.h>
#include <string>

using namespace std;

struct ScoreBoard{
    int snakeLength;
    int growth;
    int poison;
    int gateCount;
};

struct Mission{
    int achievement;
    int growth;
    int poison;
    int gateCount;
    Mission(int a, int g, int p, int gate): achievement(a), growth(g), poison(p), gateCount(gate) {}
};


class Stage{
    private:
    WINDOW* stageWin;
    WINDOW* scoreBoardWin;
    WINDOW* missionWin;
    int currentStage;
    int maxStageNumber;
    ScoreBoard scoreBoard;
    vector<Mission> missions;
    void printBanner(WINDOW* win, string title, string B, int growth, int poison, int gate);
    
    public:
    Stage();
    bool goNextStage();
    vector<vector<int>> getNextStage();
    void drawInitStage(WINDOW* mainWin);
    void drawCurrentStage();
    void drawScoreBoard();
    void drawMission();
    bool isMissionClear();
    void addGrowth();
    void addPoison();
    void passGate();
};
#endif