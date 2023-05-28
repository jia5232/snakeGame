#ifndef SnakeMap_H
#define SnakeMap_H
#include <iostream>
using namespace std;
class SnakeMap {
private:
    int row_f;
    int col_f;
    

public:
char **mapArray;
    SnakeMap(int row = 24, int col = 48);
    SnakeMap(const SnakeMap &sM);
    void setSnakeMap(char **mA);
    char** getSnakeMap();
    SnakeMap &operator=(const SnakeMap &sM);
    SnakeMap &operator=(const char **mA);
    char* operator[](int idx)const;
    friend ostream &operator<<(ostream &os, const SnakeMap &sM);
};

#endif
