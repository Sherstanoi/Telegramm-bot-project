#include <iostream>
#include <cstring>

int main() {
    char villageName[100];

    std::cout << "Введите название деревни: ";
    std::cin.getline(villageName, 100);

    std::cout << "Ваша деревня называется:" << villageName << '\n' << std::endl;
    std::cout <<"Всю жизнь, мечтая стать фермером, поэтому долго копив деньги, смогли приобрести небольшой участок в дремучей деревне, вы решиди назвать её "<<villageName << ". И вот, начинается ваш путь фермера."<< std::endl;

    char buildings[] = "🏡 Ферма 1 ур.\n"
                       "🍀 Амбар 1 ур.\n"
                       "🏬 Магазин 1 ур.\n";

    std::cout << "Куда хотите пойти?\n\n";
    std::cout << buildings;

    return 0;
}
