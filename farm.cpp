#include "farm.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ctime>

char name[100];
int money = 200;
time_t time_old = time (NULL);
time_t time_new;

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
