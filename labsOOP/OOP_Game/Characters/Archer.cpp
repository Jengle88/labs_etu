#include "Archer.h"

Archer::Archer(double health, double attackPower, double protection)
        : Character(CharacterType::SKELETON_ARCHER, health, attackPower, protection, ARCHER_LUCK) {}

bool Archer::isCriticalCase(double lucky) const {
    double checkCriticalAttack = std::sin(
            (rand() % 100 + 1 / double(std::max(rand(),1) % 100)) * luck); // есть ли способ проще? //luck >= 1, поэтому проблем нет
    return ((checkCriticalAttack - int(checkCriticalAttack)) <= ROOT_EPSILON);

}

double Archer::calcReflectionArmor() const {
    return 1 / (this->protection + 2) + 0.5; // функция 1/(x+2) + 0.5 для расчёта множителя отражения удара доспехом
}

std::vector<double> Archer::requestAttack(Character &enemy) {
    std::vector<double> actionTable(3); // таблица событий при ударе
    bool wasCriticalAttack = isCriticalCase(luck);
    double startEnemyHealth = enemy.getHealth();
    bool wasDodge;
    if (wasCriticalAttack)
        wasDodge = enemy.requestProtect(this->attackPower * ARCHER_CRITICAL_FACTOR);
    else
        wasDodge = enemy.requestProtect(this->attackPower);
    return {startEnemyHealth - enemy.getHealth(), double(wasDodge), double(wasCriticalAttack)};

}

bool Archer::requestProtect(double attackPower) {
    bool wasDodge = this->requestDodge();
    if (wasDodge)
        this->health -= attackPower * calcReflectionArmor() * ARCHER_DODGE_FACTOR;
    else
        this->health -= attackPower * calcReflectionArmor();
    return wasDodge;
}

bool Archer::requestDodge() const {
    return isCriticalCase(luck);
}

std::vector<CellPoint> Archer::makeMove(CellPoint from, CellPoint heroPos) const { // Паттерн: Strategy
    std::vector<CellPoint> res;
    res.reserve(4);
    if (Archer::inRangeVisibility(from, heroPos) && willFollowToHero()) {
        int deltaX = -(from.getX() - heroPos.getX()) /
                     std::max(1, abs(from.getX() - heroPos.getX()));
        int deltaY = -(from.getY() - heroPos.getY()) /
                     std::max(1, abs(from.getY() - heroPos.getY()));
        res.emplace_back(from.getX() + deltaX, from.getY());
        res.emplace_back(from.getX(), from.getY() + deltaY);
        return res;
    }
    for (int i = -ARCHER_MOVE; i <= ARCHER_MOVE; ++i) {
        for (int j = -ARCHER_MOVE; j <= ARCHER_MOVE; ++j) {
            if (i == 0 ^ j == 0) {
                res.emplace_back(from.getX() + i,from.getY() + j);
            }
        }
    }
    return res;
}

bool Archer::willFollowToHero() const {  // FIXME: исправить, формула неверная
    int k = int((100.0 / ARCHER_PERCENT_FOR_FOLLOW_TO_HERO) * 100);
    int num = int((rand() % 100 + double(1) / (rand() % 100)) * 100);
    if (num % k == 0)
        return true;
    return false;


//    double k = (2.0 * 3.1416 * ARCHER_PERCENT_FOR_FOLLOW_TO_HERO / std::ceil(100 / 3.1416)); // коэффициент для того, чтобы на промежутке от 0 до 100 было PERCENT корней
//    double chance = std::sin((rand() % 100 + 1 / double(std::max(rand(),1) % 100)) * k); // шанс того, что монстр пойдёт за героем
//    return std::abs(chance - int(chance)) <= ROOT_EPSILON;
}

bool Archer::inRangeVisibility(CellPoint monsterPos, CellPoint objectPos) {
    return abs(monsterPos.getX() - objectPos.getX()) <= ARCHER_RANGE_VISIBILITY && //попадает в прямоугольник видимости
           abs(monsterPos.getY() - objectPos.getY()) <= ARCHER_RANGE_VISIBILITY;

}

int Archer::getCharacterType() const {
    return this->characterType;
}

bool Archer::checkPositiveHealth() const {
    return health > 0;
}

