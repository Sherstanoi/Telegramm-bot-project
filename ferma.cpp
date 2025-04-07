#include <iostream>
#include <cstring>

int main() {
    char villageName[100];

    std::cout << "Введите название деревни: ";
    std::cin.getline(villageName, 100);

    std::cout << "Ваша деревня называется: " << villageName << std::endl;

    char buildings[] = "🏡 Ферма 1 ур.\n"
                       "🍀 Грядки 1 ур.\n"
                       "📦 Склад 1 ур.\n"
                       "🏬 Магазин 1 ур.\n";

    std::cout << "Куда хотите пойти?\n\n";
    std::cout << buildings;

    return 0;
}
