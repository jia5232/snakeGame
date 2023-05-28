#include "SnakeMap.h"
#include <iostream>
using namespace std;

SnakeMap::SnakeMap(int row, int col)
{
    row_f = row;
    col_f = col;
    mapArray = new char *[row_f];
    for (int i = 0; i < row_f; i++)
    {
        mapArray[i] = new char[col_f];
    }
    for (int i = 0; i < row_f; i++)
    {
        for (int j = 0; j < col_f; j++)
        {
            mapArray[i][j] = '-';
        }
    }
    for (int i = 0; i < row_f; i += row_f - 1)
    {
        for (int j = 0; j < col_f; j++)
        {
            mapArray[i][j] = '#';
        }
    }
    for (int i = 0; i < row_f; i++)
    {
        for (int j = 0; j < col_f; j += col_f - 1)
        {
            mapArray[i][j] = '#';
        }
    }
}
void SnakeMap::setSnakeMap(char **mA)
{
    for (int i = 0; i < row_f; i++)
    {
        for (int j = 0; j < col_f; j++)
        {
            mapArray[i][j] = mA[i][j];
        }
    }
}

char **SnakeMap::getSnakeMap()
{
    return mapArray;
}

char *SnakeMap::operator[](int idx)const
{
    return mapArray[idx];
}

SnakeMap& SnakeMap::operator=(const SnakeMap &sM)
{
    for (int i = 0; i < row_f; i++)
    {
        for (int j = 0; j < col_f; j++)
        {
            mapArray[i][j] = sM[i][j];
        }
    }
    return *this;
}

SnakeMap& SnakeMap::operator=(const char **mA)
{
    for (int i = 0; i < row_f; i++)
    {
        for (int j = 0; j < col_f; j++)
        {
            mapArray[i][j] = mA[i][j];
        }
    }
    return *this;
}

ostream &operator<<(ostream &os, const SnakeMap &sM)
{
    for (int i = 0; i < sM.row_f; i++)
    {
        for (int j = 0; j < sM.col_f; j++)
        {
            os << sM[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

