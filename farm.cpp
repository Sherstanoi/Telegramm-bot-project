#include "farm.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>

char name[100];
int money = 200;


void start() {
  std::cout << "Как вы назовете свою ферму: ";
  std::cin >> name;
  menu();
}

void OutputProperty() {
    std::cout << "У вас есть: ";
    std::cout << money << " монет\n" << ;
}

void menu() {
    std::cout << "Добро пожаловать в " << name << '\n';
    OutputProperty();

}
