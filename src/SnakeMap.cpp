#include "SnakeMap.h"
#include "Snake.h"
#include "ItemGenerator.h"
#include "GateGenerator.h"
#include <vector>
#include <ncurses.h>
using namespace std;
#define ITEM_REGEN 50
#define GAME_OVER -1
#define GAME_CONTINUE 1
SnakeMap::SnakeMap(WINDOW* mainWin,int **map, int height, int width): mainWin(mainWin), mapWidth(width), mapHeight(height)
{
    mapArray = new int*[mapHeight];
    for(int i = 0; i < mapHeight; i++){
        mapArray[i] = new int[mapHeight];
    }
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapHeight; j++){
            mapArray[i][j] = map[i][j];
        }
    }
}
void SnakeMap::mapReset(){

}
int SnakeMap::drawSnakeMap(Snake& sk, int direction, ItemGenerator& growth, ItemGenerator& poison, GateGenerator& gate){
    vector<SnakeVector> sv = sk.getSnake();
    bool isGrowth = false;
    bool isPoison = false;
    ItemCoordinate growthCor = growth.getItemCoordinate();
    ItemCoordinate poisonCor = poison.getItemCoordinate();
    mapArray[growthCor.row][growthCor.col] = 5;
    mapArray[poisonCor.row][poisonCor.col] = 6;

    GateCoordinate gate1 = gate.getGate1();
    GateCoordinate gate2 = gate.getGate2();

    if(sv.size() < 3){
        return GAME_OVER;
    }
    for(int i = 0 ; i < sv.size(); i++){
        int row = sv[i].row;
        int col = sv[i].col;
         //스네이크가 1(벽)에 접근시 리턴 -1
        if(mapArray[row][col] == 1){
            return GAME_OVER;
        }
        if (i == 0) {
            if (mapArray[row][col] == 5) {
                isGrowth = true;
            } else if (mapArray[row][col] == 6) {
                isPoison = true;
            }
            mapArray[row][col] = 3;
        } else {
            // 스네이크 헤드와 바디의 좌표가 겹칠 때 리턴 GAME_OVER
            if (row == sv[0].row && col == sv[0].col) {
                return GAME_OVER;
            }
            mapArray[row][col] = 4;
        }
    }

    for(int i = 0; i < mapHeight; i++){
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);

        for(int j = 0; j < mapWidth; j++){
            if(j % 2 != 0){
                mvwprintw(mainWin,i, j, " ");
            }else{
                if(mapArray[i][j/2] == 0){
                    mvwprintw(mainWin,i, j, "-");
                }else if(mapArray[i][j/2] == 1){
                    mvwprintw(mainWin,i, j, "#");
                }else if(mapArray[i][j/2] == 2){
                    mvwprintw(mainWin,i, j, "+");
                }
                else if(mapArray[i][j/2] == 3){
                    mvwprintw(mainWin,i, j, "^");
                }
                else if(mapArray[i][j/2] == 4){
                    mvwprintw(mainWin,i, j, "@");
                }
                else if(mapArray[i][j/2] == 5){
                    wattron(mainWin, COLOR_PAIR(1));
                    mvwprintw(mainWin,i, j, "$");
                    wattroff(mainWin, COLOR_PAIR(1));
                }
                else if(mapArray[i][j/2] == 6){
                    wattron(mainWin, COLOR_PAIR(2));
                    mvwprintw(mainWin,i, j, "P");
                    wattroff(mainWin, COLOR_PAIR(2));
                }else if(mapArray[i][j/2] == 7){
                    wattron(mainWin, COLOR_PAIR(3));
                    mvwprintw(mainWin, i, j, "G");
                    wattroff(mainWin, COLOR_PAIR(3));
                }
            } 
        }
    }

    sk.snakeMove(direction);
    if(isPoison){
        SnakeVector skPop = sk.popSnake();
        mapArray[skPop.row][skPop.col] = 0;
        skPop = sk.popSnake();
        mapArray[skPop.row][skPop.col] = 0;
    }
    else if(!isGrowth){
        SnakeVector skPop = sk.popSnake();
        mapArray[skPop.row][skPop.col] = 0;
    }
    

    if(growth.getItemTimer() >= ITEM_REGEN){
        mapArray[growthCor.row][growthCor.col] = 0;
        ItemCoordinate growthCor = growth.generateRandomItem(mapArray, mapHeight - 2);
        mapArray[growthCor.row][growthCor.col] = 5;
    }else if(isGrowth){
        ItemCoordinate growthCor = growth.generateRandomItem(mapArray, mapHeight - 2);
        mapArray[growthCor.row][growthCor.col] = 5;
    }
    if(poison.getItemTimer() >= ITEM_REGEN){
        mapArray[poisonCor.row][poisonCor.col] = 0;
        ItemCoordinate poisonCor = poison.generateRandomItem(mapArray, mapHeight - 2);
        mapArray[poisonCor.row][poisonCor.col] = 6;
    }else if(isPoison){
        ItemCoordinate poisonCor = poison.generateRandomItem(mapArray, mapHeight - 2);
        mapArray[poisonCor.row][poisonCor.col] = 6;
    }

    // Gate
    if(gate.getGateTimer() <= 0){
        mapArray[gate1.row][gate1.col] = 7;
        mapArray[gate2.row][gate2.col] = 7;
    }

    return GAME_CONTINUE;
}

