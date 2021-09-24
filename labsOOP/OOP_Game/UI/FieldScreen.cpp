#include <iostream>
#include "FieldScreen.h"


FieldScreen::FieldScreen() {
    field = nullptr;
    fieldReady = false;
}

void FieldScreen::showFieldScreen() const {

    if (!fieldReady) {
        std::cout << "Field haven`t ready yet!!!\n";
        return;
    }
    std::system("clear");
    //показ окна с полем


}

void FieldScreen::showStartingParams() {
    std::cout << "Введите значения параметров:\n";

    auto enterSizeValue = [](int &val, int defaultValue, bool (*compare_bad)(int)) {
        try {
            std::cin >> val;
        } catch(std::exception) {
            std::cout << "Введённое значение неверно. Было использовано стандартное - 20\n";
            val = defaultValue;
        }
        if (compare_bad(val)) {
            std::cout << "Введённое значение неверно. Было использовано стандартное - 20\n";
            val = defaultValue;
        }
    };

    int height, width, countWalls;
    std::cout << "Высота поля (мин = 2, макс = 1000): ";
    enterSizeValue(height, 20, [](int val) {return val < 2;});
    std::cout << "Ширина поля (мин = 2, макс = 1000): ";
    enterSizeValue(width, 20, [](int val) {return val < 2;});
    std::cout << "Количество непроходимых клеток (мин = 2, макс = 1000, макс процент покрытия - 45% от площади поля): ";
    //TODO дописать ввод кол-ва стен
//    try {
//        std::cin >> height;
//    } catch(std::exception) {
//        std::cout << "Введённое значение неверно. Было использовано стандартное - 20\n";
//        height = 20;
//    }
//    if (height < 2) {
//        std::cout << "Введённое значение неверно. Было использовано стандартное - 20\n";
//        height = 20;
//    }

}


