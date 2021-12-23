#pragma once
#include "../Entity/Characters/MainHero.h"
#include "../UI/Models/Field.h"

class RulesChecker {
public:
    virtual bool checkHero(MainHero& hero) const = 0;
    virtual bool checkField(Field& field) const = 0;
    virtual ~RulesChecker() = default;
};
