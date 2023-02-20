#include <iostream>
#include "../inc/namespaces.hpp"

int main() 
{
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::cout << "\x1B[2J\x1B[H";
    while (std::cin.good())
    {
        std::cout << "Введите цифру соответсвующую типу операции:\n 1. Шифровка\n 2. Расшифровка\n[Для выхода использовать Ctrl+D]\nОперация: ";
        int op = -1;
        std::cin >> op;
        if (op == 1) {
            encryption::crypto();
        } else if (op == 2) {
            decryption::decrypto();
        } else if (std::cin.good()) {
            std::cout << "\x1B[2J\x1B[HДруг, ну как же ты мог ошибиться?\n";
        } else {
            std::cout << "\x1B[2J\x1B[HДо встречи!\n";
        }
    }
    return 0;
}