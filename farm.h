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
void PlantSeed(TgBot::Message::Ptr message);
void Renew(TgBot::Message::Ptr message);
void CollectAll(TgBot::Message::Ptr message);

void Shop(TgBot::Message::Ptr message);
void Buy(TgBot::Message::Ptr message);
void SellSeeds(TgBot::Message::Ptr message);
void SellVegetables(TgBot::Message::Ptr message);

void Return();

void Storehouse(TgBot::Message::Ptr message);


namespace {
    bool BasicFlag = false;
    bool GardenFlag = false;
    bool StorehouseFlag = false;
    bool ShopFlag = false;
}
