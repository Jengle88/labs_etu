#pragma once
#include <string>

enum HeroKeysControl {
    // fieldScreen
    MOVE_UP,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_DOWN,
    TAKE_THING,
    START_FIGHT,
    FINISH_OUT,
    EXIT_FIELD,
    ACCEPT,
    CANCEL,
    // fightScreen
    ATTACK_ENEMY,
    SELECT_THING_UP,
    SELECT_THING_DOWN,
    USE_THING,
    EXIT_FIGHT,
    // TODO добавить кнопки для меню настроек
    SIZE_HERO_KEYS_CONTROL
};


class KeyControl {
public:
    virtual int requestKeyAction(const std::string &screen) const = 0;
    virtual std::string requestKeyLine() const = 0;
    virtual void requestKeyIgnore() const = 0;
    virtual void requestTrashIgnore() const = 0;
    virtual int requestKeyInt() const= 0;
    virtual bool resetBindChar(const std::string &screen, char key, int action) = 0;
    virtual bool checkAllKeyBound() const = 0;
    virtual bool checkRightAction(int action) const = 0;
    virtual char getKey(const std::string& screen, int action) const = 0;
    virtual void clearInputState() const = 0;
    virtual ~KeyControl() = default;
};