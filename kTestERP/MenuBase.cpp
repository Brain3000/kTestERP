#include "stdafx.h"

#include <iostream>
#include <algorithm>
#include <assert.h>
#include <windows.h>

#include "MenuBase.h"
#include "MainUtil.h"

MenuBase::Option::Option(const std::string& cap,
                         uint8_t keyCode,
                         OptionAction action,
                         const std::string& addParam) :
    m_caption(cap),
    m_keyCode(keyCode),
    m_action(action),
    m_additionalParam(addParam) {
    if (action == OptionAction::eInputString) {
        assert(!addParam.empty());
    }
}

void MenuBase::Option::show() {
    std::cout << "[" << printableKey() << "] " << m_caption << std::endl;
}

std::string MenuBase::Option::printableKey() const {
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

MenuBase::MenuBase(MainUtil* mainUtil, const std::string& caption) :
    m_mainUtil(mainUtil),
    m_caption(caption) {
    m_options.emplace("�����", 'Q', OptionAction::eExit);
}

void MenuBase::run() {
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
        uint8_t cmd = get_code();
        const auto it = std::find_if(m_options.cbegin(),
                                     m_options.cend(),
                                     [cmd](auto& opt) {
            return (opt.m_keyCode == cmd);
        });
        if (it != m_options.end()) {
            exit = true;
            switch (it->m_action) {
            case OptionAction::eRunItem:
                exit = false;
            case OptionAction::eRunItemAndExit:
                runOption(*it);
                break;
            case OptionAction::eInputString:
                inputString(*it);
                break;
            default:
                assert(!"������ �����-�� OptionAction");
            case OptionAction::eExit:
                break;
            }
        }
    }
}

void MenuBase::inputString(const Option& opt) {
    std::cout << std::endl << opt.m_additionalParam << ":";
    SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
    std::cin >> m_resultString;
    SetConsoleCP(866);// ��������� ������� �������� win-cp 1251 � ����� �����
}
