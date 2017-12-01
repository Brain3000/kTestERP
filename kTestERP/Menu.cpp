#include "stdafx.h"

#include <stdlib.h>

#include "Menu.h"
#include "MainUtil.h"

MenuOptionBase::MenuOptionBase(Page* page,
                               const std::string& cap,
                               uint8_t keyCode) :
    m_page(page),
    m_caption(cap),
    m_keyCode(keyCode)
    {}

MenuOptionBase::~MenuOptionBase() {
#ifdef _DEBUG
    std::cout << "MenuOptionBase::~MenuOptionBase\n";
#endif // _DEBUG
}

void MenuOptionBase::show() {
    std::cout << "[" << printableKey() << "] " << m_caption << std::endl;
}

std::string MenuOptionBase::printableKey() const {
    std::string res(1, m_keyCode);
    switch (m_keyCode)
    {
    case ' ':
        res = "Пробел";
        break;
    case 65:
        res = "Стрелка вверх";
        break;
    case 66:
        res = "Стрелка вниз";
        break;
    case 67:
        res = "Стрелка вправо";
        break;
    case 68:
        res = "Стрелка влево";
        break;
    default:
        break;
    }
    return res;
}


MenuOption::MenuOption(const FuncType func,
                       Page* page,
                       const std::string& cap,
                       uint8_t keyCode) :
    MenuOptionBase(page, cap, keyCode), m_func(func)
    {}

MenuOption::~MenuOption() {
#ifdef _DEBUG
    std::cout << "MenuOption::~MenuOption\n";
#endif // _DEBUG
}

Page::Page(MainUtil* mainUtil, const std::string& caption) :
           m_mainUtil(mainUtil),
           m_caption(caption) {
    std::shared_ptr<MenuOptionBase> exitOpt =
        std::make_shared<MenuOption>(nullptr, this, "Выход", 'q');
    addOption(exitOpt);
}

Page::~Page() {
#ifdef _DEBUG
    std::cout << "Page::~Page\n";
#endif // _DEBUG
}

void Page::addOption(OptionPtr option) {
    m_options.push_back(option);
}

const MainUtil* Page::mainUtil() const {
    return m_mainUtil;
}

void Page::run() const {
    bool exit(false);
    bool showOptions(true);
    while (!exit) {
        if (showOptions) {
            system("cls");
            std::cout << m_caption << std::endl;
            for (auto option : m_options) {
                std::cout << std::endl;
                option->show();
            }
        }
        uint8_t cmd = _getch();
        if (cmd == 'q') {
            exit = true;
        }
    }
}
