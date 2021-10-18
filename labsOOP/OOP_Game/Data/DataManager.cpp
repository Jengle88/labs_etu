#include "DataManager.h"

DataManager::DataManager() {
    levelToThings[1] = {
//            Thing("Железный шлем", {0, 0.5, 0, 0}, ThingObject::HELMET, true),
            Thing("Железный нагрудник", {0, 1, 0, 0}, ThingObject::ARMOR, true),
//            Thing("Деревянный щит", {0, 0.3, 0, 0}, ThingObject::SHIELD, true),
            Thing("Железный меч", {1.2, 0, 0, 0}, ThingObject::SWORD, true)
    };
    levelToThings[2] = {
//            Thing("Стальной шлем", {0, 0.8, 0, 0}, ThingObject::HELMET, true),
            Thing("Стальной нагрудник", {0, 1.3, 0, 0}, ThingObject::ARMOR, true),
//            Thing("Стальной щит", {0, 0.7, 0, 0}, ThingObject::SHIELD, true),
            Thing("Стальной меч", {1.6, 0, 0, 0}, ThingObject::SWORD, true)
    };
}

Thing DataManager::getThing(int level, int typeThing) {
    return levelToThings[level][typeThing];
}

std::vector<std::string> DataManager::getModelHeroHead() const {
    return {
              "  _____ ",
             " //.,.\\\\",
             " \\\\ _ //"
    };
            /*  _____
               //.,.\\
               \\ _ //
             */
}

std::vector<std::string> DataManager::getModelHeroBodyWait(bool withSword, bool withArmor) const {
    if (withArmor && withSword) {
        return {
                 "  _ | _   /",
                 "|//|#|\\\\ / ",
                 "|/ |#| \\/  ",
                 "|  |#|     "
                 /*  _ | _   /
                   |//|#|\\ /
                   |/ |#| \/
                   |  |#|
                  */
        };
    } else if (withSword) {
        return {
                 "    |     /",
                 "  /|-|\\  / ",
                 " / | | \\/  ",
                 "   |_|     "
                 /*    |     /
                     /|-|\  /
                    / | | \/
                      |_|
                 */
        };
    } else if (withArmor) {
        return {
            "  _ | _ ",
            " //|#|\\",
            " / |#| \\",
            "   |#|  "
        };
        /*  _ | _
           //|#|\\
           / |#| \
             |#|
        */
    } else {
        return {
          "    |   ",
          "  /|-|\\ ",
          " / | | \\",
          "   |_|  ",
        };
        /*
            |
          /|-|\
         / | | \
           |_|
         */
    }
}

std::vector<std::string> DataManager::getModelHeroLegs() const {
    return {
          "  /   \\  ",
          "_/     \\_"
    };
    /*
       /   \
     _/     \_
     */
}

std::vector<std::string> DataManager::getModelMonsterWait() const {
    return {
        "     /_// ",
        "    /0_0\\ ",
        "    |шшш| ",
        "     |-|  ",
        "//\\\\/   \\ ",
        "   |     |",
        "   |-----|",
        "   //  // ",
        "   /|  /| "
    };
    /*
          /_//
         /0_0\
         |шшш|
          |-|
     //\\/   \
        |     |
        |-----|
        //  //
        /|  /|
     */
}

std::vector<std::string> DataManager::getModelArcherWait() const {
    return {
        "     /---\\ ",
        "    -|x x|-",
        "     |vvv| ",
        "       I ww",
        " /| /|/I\\||",
        "| |-/|/I\\||",
        " \\|  |___| ",
        "      / \\  ",
        "     |   | "
    };
    /*
          /---\
         -|x x|-
          |vvv|
            I ww
      /| /|/I\||
     | |-/|/I\||
      \|  |___|
           / \
          |   |
     */
}

std::vector<std::string> DataManager::getModelGargoyleWait() const {
    return {
        "     /_//   ",
        "    /*_*\\   ",
        "    |www|   ",
        "     | |  /|",
        "/\\  /   \\//|",
        " \\\\|     |//",
        "   |-----|v ",
        "    \\\\ \\\\   ",
        "     \\\\ \\\\  "
    };
    /*
          /_//
         /*_*\
         |www|
          | |  /|
     /\  /   \//|
      \\|     |//
        |-----|v
         \\ \\
          \\ \\
     */
}
