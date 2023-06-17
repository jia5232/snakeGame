#ifndef ITEMGENERATOR_H
#define ITEMGENERATOR_H
struct ItemCoordinate{
    int row, col;
};

class ItemGenerator{
    private:
    ItemCoordinate itemCor;
    int itemTimer;
    public:
    ItemGenerator(int row, int col);
    ItemCoordinate getItemCoordinate();
    ItemCoordinate generateRandomItem(int **mapArray, int numRange);
    int getItemTimer();
};
#endif
