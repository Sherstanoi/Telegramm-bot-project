#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <tgbot/tgbot.h>
#pragma once

struct Seed{
    const char* Name;
    int TimeGrowth;
    int BuyingPrice;
    int SeedsSellingPrice;
    int Number;
    int Amount = 0;
};

struct Vegatebles {
    const char* Name;
    int VegarableSellingPrice;
    int Number;
    int Amount = 0;
};

struct product {
    const char* Name;
    int ProductPrice;
    int Amount = 0;
    int Number;
};

class SeedBed {
    public:
        time_t PlantingTime; //проверка веремени
        int SeedNumber;
        bool buse; //занята ли грядка
};

void Start();
void BasicFarm(TgBot::Message::Ptr message);

void Garden(TgBot::Message::Ptr message);
void PlantSeedOutput(TgBot::Message::Ptr message);
void PlantSeed(TgBot::Message::Ptr message, int Index, int Amount);
void CollectAllVegatables(TgBot::Message::Ptr message);
void GetGardenUpgrade(TgBot::Message::Ptr message);

void Shop(TgBot::Message::Ptr message);
void ShopOutput(TgBot::Message::Ptr message);
void BuyFirstStep(TgBot::Message::Ptr message,int Index, int Amount);
void BuySecondStep(TgBot::Message::Ptr message);
void SellSeedsOut(TgBot::Message::Ptr message);
void SellSeeds(TgBot::Message::Ptr message, int Index, int Amount);
void SellVegetablesOut(TgBot::Message::Ptr message);
void SellVegetables(TgBot::Message::Ptr message, int Index, int Amount);
int BuyShopUpgrade(TgBot::Message::Ptr message);

int UpgradeShop(int CurrentLevel,TgBot::Message::Ptr message);
void UpgradeStorehouse(int CurrentLevel, TgBot::Message::Ptr message);
void UpgradeGarden(int CurrentLevel, TgBot::Message::Ptr message);

void Return();

void StoreHouse(TgBot::Message::Ptr message);
void BuyStorehouseUpgrade(TgBot::Message::Ptr message);
void ThrowAwayItems(TgBot::Message::Ptr message);

void Vipe();

namespace {
    bool BasicFlag = false;
    bool GardenFlag = false;
    bool StorehouseFlag = false;
    bool ShopFlag = false;
    bool FirstStepInputFlag = false;
    bool SecondStepInputFlag = false;

    bool SeedInArrFlag = false;

    int UpgradeLevelCheck = 1;

    std::string MessageOut;

    int money = 3000;

    int AvailableSeed = 4; //количество доступных семян
    const int MaxAvailableSeed = 7; // максимум семян(для после прокачки)

    Seed AllSeeds[MaxAvailableSeed]; // информация семян
    int AllYourSeeds = 0;    // всего семян

    Vegatebles AllVegatables[MaxAvailableSeed]; // информация готовых овощей
    int AllYourVegatables = 0;  // все овощи
    const int MaxAvailableVegatables = 100;

    int SeedBedAmount = 5;             //количество грядок
    const int MaxSeedBedAmount = 8;        //максимум грядок
    SeedBed AllSeedBeds[MaxSeedBedAmount];  //Инфа

    int ActionScenario; //Переменная, нужная для определения некоторого набора действий
    int Index; //Индекс какого-либо продукта при покупке или продаже
    int Amount; //Количество какого-либо продукта при продаже

    int UsedSeedsInSelling[MaxAvailableSeed] = {};
    int UsedVegetablesInSelling[MaxAvailableVegatables] = {};

    const int MaxAvailableProducts = 4;
    int AvailableProducts = 1;

    product AllProducts[MaxAvailableProducts];
    int AllYourProducts = 0;

    int CurrentShopLevel = 1; //текущий уровень
    int ShopLevelling[2] = {500,1000}; //повышение уровня

    int CurrentStorehouseLevel = 1;
    int StorehouseLevelling[6] = {1,5,2,10};

    int CurrentGardenLevel =1;
    int GardenLevelling[2] = {2,4};

    int MaxItemStorage = 30;
    int MaxSeedsStorage = 20;
    }
