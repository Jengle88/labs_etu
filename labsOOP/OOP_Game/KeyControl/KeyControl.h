#pragma once
#include <string>

enum HeroKeysControl {
    // startScreen
    START_SELECT_MENU_UP,
    START_SELECT_MENU_DOWN,
    START_GO_TO_MENU,
    // fieldScreen
    FIELD_MOVE_UP,
    FIELD_MOVE_LEFT,
    FIELD_MOVE_RIGHT,
    FIELD_MOVE_DOWN,
    FIELD_TAKE_THING,
    FIELD_START_FIGHT,
    FIELD_FINISH_OUT,
    FIELD_EXIT_FIELD,
    FIELD_ACCEPT_GENERATE,
    FIELD_CANCEL_GENERATE,
    // fightScreen
    FIGHT_ATTACK_ENEMY,
    FIGHT_SELECT_THING_UP,
    FIGHT_SELECT_THING_DOWN,
    FIGHT_USE_THING,
    FIGHT_EXIT_FIGHT,
    // keySettingsScreen
    KEYSETTINGS_SELECT_MENU_UP,
    KEYSETTINGS_SELECT_MENU_DOWN,
    KEYSETTINGS_CHANGE_BIND,
    KEYSETTINGS_EXIT_SETTINGS,
    SIZE_HERO_KEYS_CONTROL
};


class KeyControl {
public:
    virtual int requestKeyAction(const std::string &screen) = 0;
    virtual char requestKeyChar() = 0;
    virtual std::string requestKeyLine() = 0;
    virtual void requestKeyIgnore() = 0;
    virtual void requestTrashIgnore() = 0;
    virtual int requestKeyInt() = 0;
    virtual bool resetBindChar(const std::string &screen, char newKey, int action) = 0;
    virtual bool checkAllKeyBound() const = 0;
    virtual bool checkRightAction(int action) const = 0;
    virtual char getKey(const std::string& screen, int action) = 0;
    virtual void clearInputState() = 0;
    virtual std::unordered_map<std::string, std::unordered_map<std::string, int>> getAllActionKeys() const  = 0;
    virtual std::unordered_map<std::string, std::unordered_map<char, int>> getAllKeysBound() const = 0;
    virtual ~KeyControl() = default;
};