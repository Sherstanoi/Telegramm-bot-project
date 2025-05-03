#include "farm.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>

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


void start(){
    AllSeeds[0].name = "Семена пшена";    AllSeeds[0].TimeGrowth = 10; AllSeeds[0].BuyCost = 4;  AllSeeds[0].SellCost = 3;  AllSeeds[0].Number = 0;
    AllSeeds[1].name = "Семена морковки"; AllSeeds[1].TimeGrowth = 20; AllSeeds[1].BuyCost = 2;  AllSeeds[1].SellCost = 1;  AllSeeds[1].Number = 1;
    AllSeeds[2].name = "Семена свеклы";   AllSeeds[2].TimeGrowth = 30; AllSeeds[2].BuyCost = 6;  AllSeeds[2].SellCost = 5;  AllSeeds[2].Number = 2;
    AllSeeds[3].name = "Семена тыквы";    AllSeeds[3].TimeGrowth = 60; AllSeeds[3].BuyCost = 12; AllSeeds[3].SellCost = 10; AllSeeds[3].Number = 3;

    AllVegatables[0].name = "Пшено";    AllVegatables[0].SellCost = 6;  AllVegatables[0].Number = 0;
    AllVegatables[1].name = "Морковка"; AllVegatables[1].SellCost = 4;  AllVegatables[1].Number = 1;
    AllVegatables[2].name = "Свекла";   AllVegatables[2].SellCost = 10; AllVegatables[2].Number = 2;
    AllVegatables[3].name = "Тыква";    AllVegatables[3].SellCost = 20; AllVegatables[3].Number = 3;
}

void basicFarm() {
    start();
    while(true) {
        std::cout << "БЛА БЛА БЛА ЛОР\nкyдa пойдем?\n 1) огород\n 2) магазин\n 3) амбар\n 4) выход наружу\n";
        int way = 0;
        std::cin >> way;
        switch (way) {
            case 1:{
                garden();
                break;
            }
            case 2:{
                shop();
                break;
            }
            case 3:{
                storehouse();
                break;
            }
            case 4:{
                return;
                break;
            }
            default:{
                std::cout << "что то не так \n";
                break;
            }
        }
    }
}


void storehouse(){
    std::cout << "Вы амбаре тут хранится ваше имущество, если оно y вас есть)\ny вас\n";
    std::cout << money << '\n';
    if (AllYouSeed != 0) {
        std::cout << "Ваши семена:\n";
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllSeeds[i].amount != 0){
                std::cout << AllSeeds[i].amount << ": " << AllSeeds[i].name << '\n';
            }
        }
    }
    if (AllYourVegatables != 0) {
        std::cout << "\nВаши овощи:\n";
        for (int i = 0; i < AvailableSeed; i++) {
            if (AllVegatables[i].amount != 0){
                std::cout << AllVegatables[i].amount << ": " << AllVegatables[i].name <<'\n'<<'\n';
            }
        }
    }
}

void shopOut() {
    const int kLengthColumn = 20;
    const int kPrecision = 10;
    std::cout << std::setw(15) << "вид" << ' ' << '\n';//<< std::setw(kLengthColumn) << " стоимость семечка (продажа/покупка)" << std::setw(kLengthColumn) << " у вас семечек" << std::setw(kLengthColumn) << " стоимость овоща" << std::setw(kLengthColumn) << " у вас овощей" << std::endl;

    for (int i = 0; i < AvailableSeed; i++) {
        std::cout  << std::setw(15) << AllVegatables[i].name << ' ' << '\n';//<< std::setw(kLengthColumn) << AllSeed[i].SellCost << '/' << AllSeed[i].BuyCost << std::setw(kLengthColumn) << AllSeed[i].amount << std::setw(kLengthColumn) << AllVegatebles[i].SellCost << std::setw(kLengthColumn) << AllVegatebles[i].amount << std::endl;
    }
}

void shop() {
    while (true) {
        shopOut();
        std::cout << "Вы хотите:\n1) купить\n2) продать семена\n3) продать овощи\n4) выйти из магазина: \n";
        int way = 0;
        std::cin >> way;
        switch (way) {
            case 1:{
                std::cout << "Введите номер продукта и количество: ";
                int Index = 0, Amount = 0;
                std::cin >> Index >> Amount;
                if (Index > 0 && Index <= AvailableSeed && Amount > 0 && AllSeeds[Index - 1].BuyCost * Amount <= money) {
                    money -= AllSeeds[Index - 1].BuyCost * Amount;
                    AllSeeds[Index - 1].amount += Amount;
                    AllYouSeed += Amount;
                } else {
                    std::cout << "ошибка ввода лол или что то другое не так";
                }
                break;
            }
            case 2:{
                std::cout << "Введите номер продукта и количество: ";
                int Index = 0, Amount = 0;
                std::cin >> Index >> Amount;
                if (Index > 0 && Index <= AvailableSeed && Amount > 0 && AllSeeds[Index - 1].amount >= Amount) {
                    money += AllSeeds[Index - 1].BuyCost * Amount;
                    AllSeeds[Index - 1].amount -= Amount;
                    AllYouSeed -= Amount;
                } else {
                    std::cout << "ошибка ввода лол или что то другое не так";
                }
                break;
            }
            case 3:{
                std::cout << "Введите номер продукта и количество: ";
                int Index = 0, Amount = 0;
                std::cin >> Index >> Amount;
                if (Index > 0 && Index <= AvailableSeed && Amount > 0 && AllVegatables[Index - 1].amount >= Amount) {
                    money += AllVegatables[Index - 1].SellCost * Amount;
                    AllVegatables[Index - 1].amount -= Amount;
                    AllYourVegatables -= Amount;
                } else {
                    std::cout << "ошибка ввода лол или что то другое не так";
                }
                break;
            }
            case 4:{
                return;
                break;
            }
            default:{
                std::cout << "ошибка ввода лол или что то другое не так\n";
            }
        }
    }
}

void gardenOut() {
    std::cout << "Вы в грядках (совет дня: Не выращивайте конаплю)\n Вот ващи грядки\n";
    time_t timeNow = time (NULL);
    for(int i = 0; i < SeedBedAmount; i++){
        if (AllSeedBeds[i].buse) {
            if (AllSeeds[AllSeedBeds[i].NumberSeed].TimeGrowth - timeNow + AllSeedBeds[i].TimeLanding > 0){
                std::cout << "🪺  " << AllSeeds[AllSeedBeds[i].NumberSeed].name << " осталось до полного созревания " << AllSeeds[AllSeedBeds[i].NumberSeed].TimeGrowth - timeNow + AllSeedBeds[i].TimeLanding << '\n';
            } else {
                std::cout << "🪺  " << AllSeeds[AllSeedBeds[i].NumberSeed].name << " созрел\n";
            }
        }else {
            std::cout << "🪹 \n";
        }
    }
}

void garden(){
    while(true) {
        gardenOut();

        if (AllYouSeed != 0) {
            std::cout << "семена: \n";
            int nomber = 1;
            for (int i = 0; i < AvailableSeed; i++) {
                if (AllSeeds[i].amount != 0){
                    std::cout << nomber << ") " << AllSeeds[i].name << ' ' << AllSeeds[i].amount << '\n';
                    nomber++;
                }
            }
            std::cout << "\n";
        } else {
            std::cout << "Увас нет семян , потому что их надо купить\n";
        }

        std::cout << "Что вы хотите сделать ?\n 1)обновить\n 2)посадить семена\n 3)собрать все\n 4)обратно\n";
        int way = 0;
        std::cin >> way;
        switch (way) {
            case 1:{
                break;
            }
            case 2:{
                std::cout << "какие семена(номер) и сколько вы хотите посадить ?\n";
                int Index = 0, Amount = 0;
                std::cin >> Index >> Amount;
                Index--;
                if (Index < 0) {
                    break;
                }
                for (int i = 0; i < AvailableSeed; i++) {
                    if (AllSeeds[i].amount != 0 && Index != 0){
                        Index--;
                    } else if (AllSeeds[i].amount != 0) {
                        Index = i;
                        break;
                    }
                }
                std::cout << Index << '\n';

                if (AllSeeds[Index].amount == 0) {
                    std::cout << "Вы чо ,у вас нет таких семян\n";
                    break;
                }
                for(int i = 0; Amount > 0 && i < SeedBedAmount; i++){
                    if (!AllSeedBeds[i].buse && AllSeeds[Index].amount > 0){
                        AllSeedBeds[i].buse = true;
                        AllSeedBeds[i].NumberSeed = Index;
                        AllSeedBeds[i].TimeLanding = time (NULL);
                        Amount--;
                        AllSeeds[Index].amount--;
                        AllYouSeed--;
                    }
                }
                if (Amount != 0) {
                    std::cout << "У вас кончились семена(мы не смогли посадить столько сколько вы хотели)\n";
                }

                break;
            }
            case 3:{
                for(int i = 0; i < SeedBedAmount; i++) {
                    storehouse();
                    if (AllSeedBeds[i].buse && AllSeeds[AllSeedBeds[i].NumberSeed].TimeGrowth - time (NULL) + AllSeedBeds[i].TimeLanding <= 0) {
                        AllSeedBeds[i].buse = false;
                        AllVegatables[AllSeeds[AllSeedBeds[i].NumberSeed].Number].amount++;
                        AllYourVegatables++;
                    }
                }
                break;
            }
            case 4:{
                return ;
            }
            default:{
                std::cout << "что то не так \n";
                break;
            }
        }
    }
}
