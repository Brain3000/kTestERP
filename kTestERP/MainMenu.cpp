#include "stdafx.h"
#include "MainMenu.h"
#include "ChoiceJobMenu.h"
#include "MainUtil.h"

MainMenu::MainMenu(MainUtil* mainUtil) :
    MenuBase(mainUtil, "������� ����")
{
    Options options = {
        {"��������� csv-�����", '1', OptionAction::eRunItem},
        {"��������� ������ ���� �����", '2', OptionAction::eRunItem},
        {"��������� ������ ������", '3', OptionAction::eRunItem},
        {"��������� ������ ����������", '4', OptionAction::eRunItem},
        {"���������� ��������� �����", '5', OptionAction::eRunItem},
    };
    m_options.insert(options.begin(), options.end());
}

void MainMenu::runOption(const Option& opt) const
{
    switch (opt.m_keyCode) {
    case '1':
        m_mainUtil->loadDataFromDir();
        break;
    case '2':
    case '3':
    case '4':
        {
        ChoiceJobMenu choiceMenu(m_mainUtil, "Something");
        choiceMenu.run();
        }
        break;
    default:
        assert(!"�������������� �����");
    };
}
