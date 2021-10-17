class Enemy {
public:
    virtual bool isCriticalCase(double lucky) = 0;
    virtual double calcReflectionArmor() = 0;
    virtual std::vector<double> requestAttack(Character &enemy) = 0; // возвращает информацию, был ли критический удар, уклонение и изменение здоровья
    virtual bool requestProtect(double attackPower) = 0; // возвращает информацию, было ли уклонение
    virtual bool requestDodge() = 0; // возвращает информацию, уклонился ли
    virtual double getHealth() const = 0;
    virtual CellPoint makeMove(CellPoint from) const = 0;
};
