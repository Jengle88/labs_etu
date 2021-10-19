#include "DataManager.h"
#include "../Characters/Monster.h"

DataManager::DataManager() {
    levelToThings[1] = {
            Thing("Железный нагрудник", {0, 1, 0, 0}, ThingObject::ARMOR, true),
            Thing("Железный меч", {1.2, 0, 0, 0}, ThingObject::SWORD, true)
    };
    levelToThings[2] = {
            Thing("Стальной нагрудник", {0, 1.3, 0, 0}, ThingObject::ARMOR, true),
            Thing("Стальной меч", {1.6, 0, 0, 0}, ThingObject::SWORD, true)
    };
}

Thing DataManager::getThing(int level, int typeThing) {
    return levelToThings[level][typeThing];
}

std::vector<std::string> DataManager::getModelHeroHead() const {
    return {
             "  _____    ",
             " //.,.\\\\   ",
             " \\\\ _ //   "
    };
            /*  _____
               //.,.\\
               \\ _ //
             */
}

std::vector<std::string> DataManager::getModelHeroBodyWait(bool withSword, bool withArmor) const {
    if (withArmor && withSword) {
        return {
//                 "  _ | _   / ",
//                 "|//|#|\\\\ /  ",
//                 "|/ |#| \\/   ",
//                 "|  |#|      "
                 "  _ | _   /",
                 " //|#|\\\\ / ",
                 " / |#| \\/  ",
                 "   |#|     "

                 /*  _ | _   /
                   |//|#|\\ /
                   |/ |#| \/
                   |  |#|
                  */
        };
    } else if (withSword) {
        return {
//                 "    |     / ",
//                 "  /|-|\\  /  ",
//                 " / | | \\/   ",
//                 "   |_|      "
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
//            "  _ | _  ",
//            " //|#|\\ ",
//            " / |#| \\ ",
//            "   |#|   "
            "    |      ",
            "  /|#|\\    ",
            " / |#| \\   ",
            "   |#|     "
        };
        /*  _ | _
           //|#|\\
           / |#| \
             |#|
        */
    } else {
        return {
//          "    |    ",
//          "  /|-|\\  ",
//          " / | | \\ ",
//          "   |_|   ",
          "    |      ",
          "  /|-|\\    ",
          " / | | \\   ",
          "   |_|     "
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
        "     //  // ",
        "     /|  /| "
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
        "        / \\  ",
        "       |   | "
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
        "      \\\\ \\\\   ",
        "       \\\\ \\\\  ",
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

std::vector<std::string> DataManager::getEnemy(int enemyType) const {
    switch (enemyType) {
        case CharacterType::MONSTER:
            return getModelMonsterWait();
        case CharacterType::SKELETON_ARCHER:
            return getModelArcherWait();
        case CharacterType::GARGOYLE:
            return getModelGargoyleWait();
        default:
            return {};
    }
}

std::vector<std::string> DataManager::getHero(bool withSword, bool withArmor) const {
    auto heroHead = getModelHeroHead();
    auto heroBody = getModelHeroBodyWait(withSword, withArmor);
    auto heroLegs = getModelHeroLegs();
    std::vector<std::string> mainHeroModel;
    mainHeroModel.reserve(heroHead.size() + heroBody.size() + heroLegs.size());
    std::move(heroHead.begin(),  heroHead.end(), std::back_inserter(mainHeroModel));
    std::move(heroBody.begin(),  heroBody.end(), std::back_inserter(mainHeroModel));
    std::move(heroLegs.begin(),  heroLegs.end(), std::back_inserter(mainHeroModel));
    return mainHeroModel;
}
