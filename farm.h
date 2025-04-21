#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

struct Seed{
    const char* name;
    int TimeGrowth;
    int harvest;
    int BuyCost;
    int SellCost;
    int Number;
};

struct Vegatebles {
    const char* name;
    int SellCost;
    int Number;
    int amount;  //ЧТО ЭТО ???
};

class SeedBed {
    public:
        time_t TimeLanding;
        Seed yes;
        bool buse; //занято?
};

void garden();
void shop();
void storehouse();
void basicFarm();
void menu();
