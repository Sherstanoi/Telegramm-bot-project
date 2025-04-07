#include <iostream>
#include <string>
#include <locale>

int main() {
    std::string villageName;

    std::cout << "Введите название деревни: ";
    std::getline(std::cin, villageName);

    std::cout << "Вы деревня называется: " << villageName << std::endl;

    std::wstring buildings = L"\U0001F3E0 Ферма 1 ур.\n"
                            L"\U0001F3D8 Грядки 1 ур.\n"
                            L"\U0001F3DA Склад 1 ур.\n"
                            L"\U0001F332 Магазин 1 ур.\n";

    std::wcout.imbue(std::locale("")); // Убедитесь, что система поддерживает UTF-8

    std::wcout << L"Куда хотите пойти\n\n";
    std::wcout << buildings << std::endl;

    return 0;
}
