#include <map>
#include "../Objects/Thing.h"

class DataManager {
    std::map<int, std::vector<Thing>> levelToThings;
public:
    DataManager();
    Thing getThing(int level, int typeThing);
};
