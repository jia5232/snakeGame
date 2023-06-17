#include "ItemGenerator.h"
#include <iostream>
#include <random>
using namespace std;
ItemGenerator::ItemGenerator(int row, int col){
    itemCor.row = row;
    itemCor.col = col;
    itemTimer = 0;
}

ItemCoordinate ItemGenerator::generateRandomItem(int **mapArray, int numRange)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> randomNum(1, numRange);

    ItemCoordinate temp;

    do
    {
        temp.row = randomNum(gen);
        temp.col = randomNum(gen);
    } while (mapArray[temp.row][temp.col] != 0);

    itemCor = temp;
    itemTimer = 0;
    return itemCor;
}
int getItemTimer(int itemType);

ItemCoordinate ItemGenerator::getItemCoordinate()
{
    itemTimer++;
    return itemCor;
}

int ItemGenerator::getItemTimer()
{
    return itemTimer;
}