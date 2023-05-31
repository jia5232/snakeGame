#include "GateGenerator.h"
#include <iostream>
#include <random>
using namespace std;
GateGenerator::GateGenerator(int **mapArray){
    generateRandomGate(mapArray);
    gateTimer = 50;
}

void GateGenerator::generateRandomGate(int **mapArray)
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

    gateTimer = 50;
    cout << gate1.row << " " << gate1.col  << endl;
    cout << gate2.row << " " << gate2.col  << endl;
}

GateCoordinate GateGenerator::getGate1()
{
    gateTimer--;
    return gate1;
}
GateCoordinate GateGenerator::getGate2()
{
    gateTimer--;
    return gate2;
}

int GateGenerator::getGateTimer()
{
    return gateTimer;
}