#pragma once

#include <string>
#include <list>
#include <memory>

enum class MenuOptionAction {
    eGoBack,
    eShowPage,
//    eExit
};

struct MenuOption {
    MenuOption(const std::string& cap, uint8_t keyCode, MenuOptionAction action);
    void show();

    const std::string m_caption;
    const uint8_t m_keyCode = ' ';
    const MenuOptionAction m_action;

private:
    std::string printableKey() const;

};

class MainUtil;

using Options = std::list<MenuOption>;

class Page
{
public:
    Page(MainUtil* mainUtil, const std::string& caption);
    void addOption(const MenuOption& option);
    const MainUtil* mainUtil() const;
    void run() const;

private:
    MainUtil* m_mainUtil;
    const std::string m_caption;
    Options m_options;
};

