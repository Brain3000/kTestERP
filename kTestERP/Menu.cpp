#include "stdafx.h"

#include <stdlib.h>

#include "Menu.h"
#include "MainUtil.h"

MenuOption::MenuOption(const std::string& cap,
                       uint8_t keyCode,
                       MenuOptionAction action) :
    m_caption(cap),
    m_keyCode(keyCode),
    m_action(action)
    {}

void MenuOption::show() {
    std::cout << "[" << printableKey() << "] " << m_caption << std::endl;
}

std::string MenuOption::printableKey() const {
    std::string res(1, m_keyCode);
    switch (m_keyCode)
    {
    case ' ':
        res = "������";
        break;
    case 65:
        res = "������� �����";
        break;
    case 66:
        res = "������� ����";
        break;
    case 67:
        res = "������� ������";
        break;
    case 68:
        res = "������� �����";
        break;
    default:
        break;
    }
    return res;
}

Page::Page(MainUtil* mainUtil, const std::string& caption) :
           m_mainUtil(mainUtil),
           m_caption(caption) {
    m_options.emplace_back("�����", 'q', MenuOptionAction::eGoBack);
}

void Page::addOption(const MenuOption& option) {
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
                option.show();
            }
        }
        // ����� ��� ���� ��������������� ���������� ������
        // ����� ��������� ��������� � ������� �����
        uint8_t cmd = _getch();
        const auto it = std::find_if(m_options.cbegin(),
                                     m_options.cend(),
                                     [cmd](auto& opt) {
            return (opt.m_keyCode == cmd);
        });
        if (it != m_options.end()) {
            switch (it->m_action) {
            case MenuOptionAction::eShowPage:
                assert(false);
                break;
            default:
                assert(false);
            case MenuOptionAction::eGoBack:
                exit = true;
                break;
            }
        }
    }
}
