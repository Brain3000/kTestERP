#include "stdafx.h"

#include <iostream>
#include <algorithm>
#include <assert.h>
#include <windows.h>

#include "CustomMenu.h"
#include "MainUtil.h"

CustomMenu::Option::Option(const std::string& cap,
                         int keyCode,
                         OptionAction action,
                         const std::string& addParam) :
    m_caption(cap),
    m_keyCode(keyCode),
    m_action(action),
    m_additionalParam(addParam) {
}

void CustomMenu::Option::show() {
    std::cout << "[" << printableKey() << "] " << m_caption << std::endl;
}

std::string CustomMenu::Option::printableKey() const {
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

CustomMenu::CustomMenu(MainUtil* mainUtil, const std::string& caption) :
    m_mainUtil(mainUtil),
    m_caption(caption) {
    m_options.emplace("�����", 'Q', OptionAction::eExit);
}

void CustomMenu::run() {
    bool exit(false);
    bool showOptions(true);
    while (!exit) {
        const Options& opts = options();
        if (showOptions) {
            system("cls");
            std::cout << m_caption << std::endl;
            for (auto option : opts) {
                std::cout << std::endl;
                option.show();
            }
        }
        // ����� ��� ���� ��������������� ���������� ������
        // ����� ��������� ��������� � ������� �����
        int cmd = get_code();
        const auto it = std::find_if(opts.cbegin(),
                                     opts.cend(),
                                     [cmd](auto& opt) {
            return (opt.m_keyCode == cmd);
        });
        if (it != opts.end()) {
            exit = true;
            switch (it->m_action) {
            case OptionAction::eRunItem:
                exit = false;
            case OptionAction::eRunItemAndExit:
                runOption(*it);
                break;
            default:
                assert(!"������ �����-�� OptionAction");
            case OptionAction::eExit:
                break;
            }
        }
    }
}
