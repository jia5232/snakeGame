#include "SnakeMap.h"
#include "Snake.h"
#include <vector>
#include <ncurses.h>
using namespace std;

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
    // for(int i = 0; i < mapHeight; i++){
    //     for(int j = 0; j < mapHeight; j++){
    //         cout << mapArray[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}
void SnakeMap::mapReset(){

}
void SnakeMap::drawSnakeMap(Snake& sk, int direction){
    sk.snakeMove(direction);
    vector<SnakeVector> sv = sk.getSnake();
    int tempMapArray[21][21];
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapHeight; j++){
            tempMapArray[i][j] = mapArray[i][j];
            }
    }
    for(int i = 0 ; i < sv.size(); i++){
        int row = sv[i].row;
        int col = sv[i].col;
        if(i == 0){
            tempMapArray[row][col] = 3;
        }else{
            tempMapArray[row][col] = 4;
        }
    }
    // for(int i = 0; i < mapHeight; i++){
    //     for(int j = 0; j < mapWidth; j++){
    //         cout << tempMapArray[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            if(j % 2 != 0){
                mvwprintw(mainWin,i, j, " ");
            }else{
                if(tempMapArray[i][j/2] == 2){
                mvwprintw(mainWin,i, j, "+");
                }else if(tempMapArray[i][j/2] == 0){
                    mvwprintw(mainWin,i, j, "-");
                }else if(tempMapArray[i][j/2] == 1){
                    mvwprintw(mainWin,i, j, "#");
                }
                else if(tempMapArray[i][j/2] == 3){
                    mvwprintw(mainWin,i, j, "^");
                }
                else if(tempMapArray[i][j/2] == 4){
                    mvwprintw(mainWin,i, j, "@");
                }
            }
            
            
        }
    }
}



// for(int row = 0; row < height; row++){
//         for(int col = 0; col < width; col++){
//             if( row == 0 && col == 0 || row == height - 1 && col == width - 1 || row == height - 1 && col == 0 || row == 0 && col == width -1){
//                 mvwprintw(mainWin, row, col, "+");
//             }
//             else if(row == 0 || col == 0 || row == height - 1 || col == width - 1){
//                 mvwprintw(mainWin, row, col, "#");
//             }else if(col % 2 == 0) {
//                 mvwprintw(mainWin, row, col, "-");
//             }
//         }
//     }