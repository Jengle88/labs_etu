#pragma once
struct CharacterRules {
    CharacterRules(const std::string &name, double health, double attackPower, double protection, double luck,
                   int visibility, double criticalFactor, double dodgeFactor, int percentForFollowToHero,
                   int lengthMove, int chanceToBeGenerate) : name(name), health(health), attackPower(attackPower),
                                                             protection(protection), luck(luck), visibility(visibility),
                                                             criticalFactor(criticalFactor), dodgeFactor(dodgeFactor),
                                                             percentForFollowToHero(percentForFollowToHero),
                                                             lengthMove(lengthMove),
                                                             chanceToBeGenerate(chanceToBeGenerate) {}

    // -1 - параметр не используется
    std::string name = "";
    double health = 0;
    double attackPower = 0;
    double protection = 0;
    double luck = 0;
    int visibility = 0;
    double criticalFactor = 0;
    double dodgeFactor = 0;
    int percentForFollowToHero = 0;
    int lengthMove = 0;
    int chanceToBeGenerate = 0; // -1 - генерируется единожды
};
