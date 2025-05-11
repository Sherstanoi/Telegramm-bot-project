#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <tgbot/tgbot.h>
#pragma once

struct Seed{
    const char* Name;
    int TimeGrowth;
    int BuyCost;
    int SellCost;
    int Number;
    int amount = 0;
};

struct Vegatebles {
    const char* Name;
    int SellCost;
    int Number;
    int amount = 0;
};

class SeedBed {
    public:
        time_t TimeLanding; //функция
        int NumberSeed;
        bool buse; //занято?
};

void Start();
void BasicFarm(TgBot::Message::Ptr message);

void Garden(TgBot::Message::Ptr message);
void PlantSeedOut(TgBot::Message::Ptr message);
void PlantSeed(TgBot::Message::Ptr message, int Index, int Amount);
void CollectAll(TgBot::Message::Ptr message); //АЛОООООООО ГДЕЕЕЕ

void ShopOut(TgBot::Message::Ptr message);
void BuyFirstStep(TgBot::Message::Ptr message,int Index, int Amount);
void BuySecondStep(TgBot::Message::Ptr message);
int* SellSeedsOut(TgBot::Message::Ptr message);
void SellSeeds(TgBot::Message::Ptr message, int Index, int Amount);
void SellVegetables(TgBot::Message::Ptr message);

void Return();

void StoreHouse(TgBot::Message::Ptr message);


namespace {
    bool BasicFlag = false;
    bool GardenFlag = false;
    bool StorehouseFlag = false;
    bool ShopFlag = false;
    bool FirstStepInFlag = false;
    bool SecondStepInFlag = false;


    std::string MessageOut;

    int money = 200;

    int AvailableSeed = 4; //количество доступных семян
    const int MaxAvailableSeed = 7; // максимум семян(для после прокачки)

    Seed AllSeeds[MaxAvailableSeed]; // информация семян
    int AllYouSeed = 0;    // всего семян.121

    Vegatebles AllVegatables[MaxAvailableSeed]; // информация готовых овощей
    int AllYourVegatables = 0;     // все овощи

    int SeedBedAmount = 5;             //количество грядок
    const int MaxSeedBedAmount = 8;        //максимум грядок
    SeedBed AllSeedBeds[MaxSeedBedAmount];  //Инфа

    int ActionScenario; //Переменная, нужная для определения некоторого набора действий
    int Index; //Индекс какого-либо продукта при покупке или продаже
    int Amount; //Количество какого-либо продукта при продаже

    int UsedSeedsInSelling[] = {};
    int UsedSeedsInSellingSec[MaxAvailableSeed] = {};
    }
