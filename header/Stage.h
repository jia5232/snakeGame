#ifndef STAGE_H
#define STAGE_H
#include <vector>
#include <ncurses.h>

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
    WINDOW* mainWin;
    int currentStage;
    int maxStageNumber;
    ScoreBoard scoreBoard;
    vector<Mission> missions;
    void printBanner(string title, string B, int growth, int poison, int gate);

    public:
    Stage();
    Stage(WINDOW* mainWin);
    bool goNextStage();
    void drawCurrentStage();
    void drawScoreBoard();
    void drawMission();
    bool isMissionClear();
    void addGrowth();
    void addPoison();
    void passGate();
};
#endif