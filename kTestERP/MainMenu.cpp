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

void MainMenu::runOption(const Option& opt)
{
    using UnitKindMap = std::unordered_map<uint8_t, UnitKind>;
    UnitKindMap uninKindMap = {
        {'2', UnitKind::eCompany},
        {'3', UnitKind::eDepartament},
        {'4', UnitKind::eEmployer},
    };
    switch (opt.m_keyCode) {
    case '1':
        m_mainUtil->loadDataFromDir();
        break;
    case '2':
    case '3':
    case '4':
        {
        ChoiceJobMenu choiceMenu(m_mainUtil, kind_to_str(uninKindMap.at(opt.m_keyCode)));
        choiceMenu.run();
        }
        break;
    case '5':
        assert(!"��� �� �������");
    default:
        assert(!"�������������� �����");
    };
}
