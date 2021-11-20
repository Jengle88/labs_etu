#pragma once
struct ThingRules {
    std::string nameThing;
    std::map<std::string, double> properties; // берём только нужные свойства
    int level = 0;
    bool isVisual = false;
    int typeObject;
    ThingRules(const std::string &nameThing, const std::map<std::string, double> &properties, int level, bool isVisual, int typeObject) : properties(properties), nameThing(nameThing), level(level), isVisual(isVisual), typeObject(typeObject) {}
};
