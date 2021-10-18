#include "Monster.h"

Monster::Monster(double health, double attackPower, double protection)
        : Character(CharacterType::MONSTER, health, attackPower, protection, MONSTER_LUCK) {}

bool Monster::requestProtect(double attackPower) {
    bool wasDodge = this->requestDodge();
    if (wasDodge)
        this->health -= attackPower * calcReflectionArmor() * MONSTER_DODGE_FACTOR;
    else
        this->health -= attackPower * calcReflectionArmor();
    return wasDodge;
}

bool Monster::requestDodge() const {
    return isCriticalCase(luck);
}

std::vector<double> Monster::requestAttack(Character &enemy) {
    std::vector<double> actionTable(3); // таблица событий при ударе
    bool wasCriticalAttack = isCriticalCase(luck);
    double startEnemyHealth = enemy.getHealth();
    bool wasDodge;
    if (wasCriticalAttack)
        wasDodge = enemy.requestProtect(this->attackPower * MONSTER_CRITICAL_FACTOR);
    else
        wasDodge = enemy.requestProtect(this->attackPower);
    return {double(wasCriticalAttack), double(wasDodge), startEnemyHealth - enemy.getHealth()};
}

std::vector<CellPoint> Monster::makeMove(CellPoint from, CellPoint heroPos) const { // Паттерн: Strategy
    std::vector<CellPoint> res;
    res.reserve(4);
    if (Monster::inRangeVisibility(from, heroPos) && willFollowToHero()) {
        int deltaX = -(from.getX() - heroPos.getX()) /
                     std::max(1, abs(from.getX() - heroPos.getX()));
        int deltaY = -(from.getY() - heroPos.getY()) /
                     std::max(1, abs(from.getY() - heroPos.getY()));
        res.emplace_back(from.getX() + deltaX, from.getY());
        res.emplace_back(from.getX(), from.getY() + deltaY);
        return res;
    }
    for (int i = -MONSTER_MOVE; i <= MONSTER_MOVE; ++i) {
        for (int j = -MONSTER_MOVE; j <= MONSTER_MOVE; ++j) {
            if (i == 0 ^ j == 0) {
                res.emplace_back(from.getX() + i,from.getY() + j);
            }
        }
    }
    return res;
}

bool Monster::willFollowToHero() const { // FIXME: исправить, формула неверная
    double k = (2.0 * 3.1416 * MONSTER_PERCENT_FOR_FOLLOW_TO_HERO / std::ceil(100 / 3.1416)); // коэффициент для того, чтобы на промежутке от 0 до 100 было PERCENT корней
    double chance = std::sin((rand() % 100 + 1 / double(std::max(rand(),1) % 100)) * k); // шанс того, что монстр пойдёт за героем
    return std::abs(chance - int(chance)) <= ROOT_EPSILON;
}

bool Monster::inRangeVisibility(CellPoint monsterPos, CellPoint objectPos) {
    return abs(monsterPos.getX() - objectPos.getX()) <= MONSTER_RANGE_VISIBILITY && //попадает в прямоугольник видимости
           abs(monsterPos.getY() - objectPos.getY()) <= MONSTER_RANGE_VISIBILITY;
}

bool Monster::isCriticalCase(double lucky) const {
    double checkCriticalAttack = std::sin(
            (rand() % 100 + 1 / double(std::max(rand(),1) % 100)) * luck); // есть ли способ проще? //luck >= 1, поэтому проблем нет
    return ((checkCriticalAttack - int(checkCriticalAttack)) <= ROOT_EPSILON);
}

double Monster::calcReflectionArmor() const {
    return 1 / (this->protection + 2) + 0.5; // функция 1/(x+2) + 0.5 для расчёта множителя отражения удара доспехом
}

int Monster::getCharacterType() const {
    return this->characterType;
}

bool Monster::checkPositiveHealth() const {
    return health > 0;
}

