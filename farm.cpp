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
int YouSeed[LotSeed]; // количество каждого вида

int ListSeedBad = 5;
const int LotSeedBad = 8;
Garden AllSeedBad[LotSeedBad];


void start(){
    AllSeed[0].name = "Морковь";AllSeed[0].harvest = 4; AllSeed[0].TimeGrowth = 20; AllSeed[0].cost = 4;
    AllSeed[1].name = "Пшено";  AllSeed[1].harvest = 6; AllSeed[1].TimeGrowth = 10; AllSeed[1].cost = 2;
    AllSeed[2].name = "Свекла"; AllSeed[2].harvest = 4; AllSeed[2].TimeGrowth = 30; AllSeed[2].cost = 6;
    AllSeed[3].name = "Тыква";  AllSeed[3].harvest = 2; AllSeed[3].TimeGrowth = 60; AllSeed[3].cost = 12;
}

void storehouse(){
    std::cout << "Вы амбаре тут хранится ваше имущество, если оно у вас есть)\ny вас\n";
    std::cout << money << " монет ";
    for (int i = 0; i < ListSeed; i++) {
        if (YouSeed[i] != 0){
            std::cout << YouSeed[i] << ' ' << AllSeed[i].name << '\n';
        }
    }
}

void shop() {
    while (true) {
        std::cout << "Вы в магазине тут можно типо покупать и продавать семена и другую хрень которой пока нет\n вот что y нас есть: \n";
        for (int i = 0; i < ListSeed; i++) {
            std::cout << i + 1 <<") " <<  AllSeed[i].name << ' ' << AllSeed[i].cost << '\n';
        }
        std::cout << "Вы хотите:\n(1) купить\n(2) продать\n(3) выйти из магазина: \n";
        int way = 0;
        std::cin >> way;
        switch (way) {
            case 1:{
                std::cout << "Введите номер продукта и количество: ";
                int ind = 0, lot = 0;
                std::cin >> ind >> lot;
                if (ind > 0 && ind <= ListSeed && lot > 0 && AllSeed[ind - 1].cost * lot <= money) {
                    money -= AllSeed[ind - 1].cost * lot;
                    YouSeed[ind - 1] += lot;
                } else {
                    std::cout << "ошибка ввода лол или что то другое не так";
                }
                break;
            }
            case 2:{
                std::cout << "Введите номер продукта и количество: ";
                int ind = 0, lot = 0;
                std::cin >> ind >> lot;
                if (ind > 0 && ind <= ListSeed && lot > 0 && YouSeed[ind - 1] >= lot) {
                    money += AllSeed[ind - 1].cost * lot;
                    YouSeed[ind - 1] -= lot;
                } else {
                    std::cout << "ошибка ввода лол или что то другое не так";
                }
                break;
            }
            case 3:{
                return;
                break;
            }
            default:{
                std::cout << "ошибка ввода лол или что то другое не так";
            }
        }
    }
}


void basicFarm() {
    start();
    while(true) {
        std::cout << "БЛА БЛА БЛА ЛОР\nкуда пойдем?\n 1) огород\n 2) магазин\n 3) амбар\n";
        int way = 0;
        std::cin >> way;
        switch (way) {
            case 1:{
                //garden();
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
            default:{
                return;
                std::cout << "что то не так \n";
            }
        }
    }
}
/*****************************************
void time() {
    while (true){
        int kolichestvo_dney;

        time_new = time (NULL);
        //kolichestvo_dney = (time_new/3600)/24;
        std::cout << "Сейчас: " << asctime(localtime(&time_new)) << "\nс прошлого обновления прошло: " << time_new - time_old << '\n';
        time_old = time_new;
        std::cin.get();
        char a;
        std::cin >> a;
        if (a == 'y') {
            break;
        }
    }
}
*/
