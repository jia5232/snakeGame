#ifndef GATEGENERATOR_H
#define GATEGENERATOR_H
struct GateCoordinate{
    int row, col;
};

class GateGenerator{
    private:
    GateCoordinate gate1;
    GateCoordinate gate2;
    int gateTimer;
    public:
    GateGenerator(int **mapArray);
    GateCoordinate getGate1();
    GateCoordinate getGate2();
    void generateRandomGate(int **mapArray);
    int getGateTimer();
};
#endif