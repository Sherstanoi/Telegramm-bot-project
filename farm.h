#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

struct Seed{
    char* name;
    int TimeGrowth;
    int harvest;
    int cost;
};

class Garden {
    private:
        time_t TimeLanding;
    public:
        bool buse;
};

void garden();
void shop();
void storehouse();
void basicFarm();
void menu();
