#include "farm.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ctime>

int money = 200;

int ListSeed = 4; //количество доступных семян
const int LotSeed = 7; // максимум семян(для после прокачки)

Seed AllSeed[LotSeed]; // информация семян
int YourSeeds[LotSeed];// количество каждого вида
int AllYouSeed = 0;    // всего семян

Vegatebles AllVegatebles[LotSeed]; // информация готовых овощей
int YourVegatebles [LotSeed]; // количество каждого вида
int AllYouVagetebles = 0;     // все овощи

int ListSeedBed = 5;             //количество грядок🪺🪹
const int LotSeedBed = 8;        //максимум грядок
SeedBed AllSeedBad[LotSeedBed];  //Инфа


void start(){
    AllSeed[0].name = "Семена пшена";    AllSeed[0].TimeGrowth = 10; AllSeed[0].BuyCost = 4;  AllSeed[0].SellCost = 3;  AllSeed[0].Number = 0;
    AllSeed[1].name = "Семена морковки"; AllSeed[1].TimeGrowth = 20; AllSeed[1].BuyCost = 2;  AllSeed[1].SellCost = 1;  AllSeed[1].Number = 1;
    AllSeed[2].name = "Семена свеклы";   AllSeed[2].TimeGrowth = 30; AllSeed[2].BuyCost = 6;  AllSeed[2].SellCost = 5;  AllSeed[2].Number = 2;
    AllSeed[3].name = "Семена тыквы";    AllSeed[3].TimeGrowth = 60; AllSeed[3].BuyCost = 12; AllSeed[3].SellCost = 10; AllSeed[3].Number = 3;

    AllVegatebles[0].name = "Пшено";    AllVegatebles[0].SellCost = 6;  AllVegatebles[0].Number = 0;
    AllVegatebles[1].name = "Морковка"; AllVegatebles[1].SellCost = 4;  AllVegatebles[1].Number = 1;
    AllVegatebles[2].name = "Свекла";   AllVegatebles[2].SellCost = 10; AllVegatebles[2].Number = 2;
    AllVegatebles[3].name = "Тыква";    AllVegatebles[3].SellCost = 20; AllVegatebles[3].Number = 3;
}

void storehouse(){
    std::cout << "Вы амбаре тут хранится ваше имущество, если оно y вас есть)\ny вас\n";
    std::cout << money << '\n';
    if (AllYouSeed != 0) {
        std::cout << "Ваши семена:\n";
        for (int i = 0; i < ListSeed; i++) {
            if (YourSeeds[i] != 0){
                std::cout << YourSeeds[i] << ": " << AllSeed[i].name << '\n';
            }
        }
    }
    if (AllYouVagetebles != 0) {
        std::cout << "\nВаши овощи:\n";
        for (int i = 0; i < ListSeed; i++) {
            if (YourVegatebles[i] != 0){
                std::cout << YourVegatebles[i] << ": " << AllVegatebles[i].name << '\n\n';
            }
        }
    }
}

void shop() {
    storehouse();
    while (true) {
        std::cout << "Вы в магазине тут можно типо покупать и продавать семена и другую хрень которой пока нет\n вот что y нас есть: \n";
        for (int i = 0; i < ListSeed; i++) {
            std::cout << i + 1 <<") " <<  AllSeed[i].name << ' ' << AllSeed[i].BuyCost << '\n';
        }

        std::cout << "Вы хотите:\n1) купить\n2) продать семена\n3) продать овощи\n4) выйти из магазина: \n";
        int way = 0;
        std::cin >> way;
        switch (way) {
            case 1:{
                std::cout << "Введите номер продукта и количество: ";
                int ind = 0, lot = 0;
                std::cin >> ind >> lot;
                if (ind > 0 && ind <= ListSeed && lot > 0 && AllSeed[ind - 1].BuyCost * lot <= money) {
                    money -= AllSeed[ind - 1].BuyCost * lot;
                    YourSeeds[ind - 1] += lot;
                    AllYouSeed += lot;
                } else {
                    std::cout << "ошибка ввода лол или что то другое не так";
                }
                break;
            }
            case 2:{
                std::cout << "Введите номер продукта и количество: ";
                int ind = 0, lot = 0;
                std::cin >> ind >> lot;
                if (ind > 0 && ind <= ListSeed && lot > 0 && YourSeeds[ind - 1] >= lot) {
                    money += AllSeed[ind - 1].BuyCost * lot;
                    YourSeeds[ind - 1] -= lot;
                    AllYouSeed -= lot;
                } else {
                    std::cout << "ошибка ввода лол или что то другое не так";
                }
                break;
            }
            case 3:{
                std::cout << "Введите номер продукта и количество: ";
                int ind = 0, lot = 0;
                std::cin >> ind >> lot;
                if (ind > 0 && ind <= ListSeed && lot > 0 && YourVegatebles[ind - 1] >= lot) {
                    money += AllVegatebles[ind - 1].SellCost * lot;
                    YourVegatebles[ind - 1] -= lot;
                    AllYouVagetebles -= lot;
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
    for(int i = 0; i < ListSeedBed; i++){
        if (AllSeedBad[i].buse) {
            if (AllSeed[AllSeedBad[i].NumberSeed].TimeGrowth - timeNow + AllSeedBad[i].TimeLanding > 0){
                std::cout << "🪺  " << AllSeed[AllSeedBad[i].NumberSeed].name << " осталось до полного созревания " << AllSeed[AllSeedBad[i].NumberSeed].TimeGrowth - timeNow + AllSeedBad[i].TimeLanding << '\n';
            } else {
                std::cout << "🪺  " << AllSeed[AllSeedBad[i].NumberSeed].name << " созрел\n";
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
            for (int i = 0; i < ListSeed; i++) {
                if (YourSeeds[i] != 0){
                    std::cout << nomber << ") " << AllSeed[i].name << ' ' << YourSeeds[i] << '\n';
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
                int ind = 0, lot = 0;
                std::cin >> ind >> lot;
                ind--;
                for (int i = 0; i < ListSeed; i++) {
                    if (YourSeeds[i] != 0 && ind != 0){
                        ind--;
                    } else if (YourSeeds[i] != 0) {
                        ind = i;
                        break;
                    }
                }
                std::cout << ind << '\n';

                if (YourSeeds[ind] == 0) {
                    std::cout << "Вы чо ,у вас нет таких семян\n";
                    break;
                }
                for(int i = 0; lot > 0 && i < ListSeedBed; i++){
                    if (!AllSeedBad[i].buse && YourSeeds[ind] > 0){
                        AllSeedBad[i].buse = true;
                        AllSeedBad[i].NumberSeed = ind;
                        AllSeedBad[i].TimeLanding = time (NULL);
                        lot--;
                        YourSeeds[ind]--;
                        AllYouSeed--;
                    }
                }
                if (lot != 0) {
                    std::cout << "Увас кончились семена(, мы не смогли посадить столько сколько вы хотели\n";
                }

                break;
            }
            case 3:{
                for(int i = 0; i < ListSeedBed; i++) {
                    storehouse();
                    if (AllSeedBad[i].buse && AllSeed[AllSeedBad[i].NumberSeed].TimeGrowth - time (NULL) + AllSeedBad[i].TimeLanding <= 0) {
                        AllSeedBad[i].buse = false;
                        YourVegatebles[AllSeed[AllSeedBad[i].NumberSeed].Number]++;
                        AllYouVagetebles++;
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

/*
Список багов/предложений по реализации:
1) можно посадить семечко, когда у тебя нет этого семечка,
2)функция "собрать выбранное" пока не работет, в целом, если хочешь, её можно исключить
3)нужна продажа овощей, но ты об этом итак говорила
4)смотри,можно в массиве seed поменять названия на "семена моркови", и ты в а баре можешь писать типаи
 "ваши семена:
семена моркови: 5

Ваши овощи:
Морковь: 6"
Сможешь так?

Косметические фиксы:
1)пожалуйста,сделай отступ после смайлик посаженного огорода
2)при продаже желательно выводить, что у тебя есть

1)ввести amount в структуру seed для реализации вывода, который "ваши семена", в таком случае:
А) ты изменяешь amount при покупке/продаже(можно функцией, если хочешь понтануться)
Б) при выводе ты идёшь по массиву и если amount != 0, выводишь информацию об этом семечке
*/
