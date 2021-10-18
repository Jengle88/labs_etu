#include <map>
#include "../Objects/Thing.h"

class DataManager {
    std::map<int, std::vector<Thing>> levelToThings;

public:
    DataManager();
    Thing getThing(int level, int typeThing);
    // Герой
    std::vector<std::string> getModelHeroHead();
    std::vector<std::string> getModelHeroBodyWait(bool withSword = false, bool withArmor = false);
    std::vector<std::string> getModelHeroLegs();
    // Враги
    std::vector<std::string> getModelMonsterWait();
    std::vector<std::string> getModelArcherWait();
    std::vector<std::string> getModelGargoyleWait();
};
