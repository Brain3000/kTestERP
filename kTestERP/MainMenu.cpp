#include "stdafx.h"
#include "MainMenu.h"
#include "ChoiceJobMenu.h"
#include "ChoiceDeptMenu.h"
#include "MainUtil.h"
#include "Company.h"

MainMenu::MainMenu(MainUtil* mainUtil) :
    MenuBase(mainUtil, "������� ����")
{
    Options options = {
        {"��������� csv-�����", '1', OptionAction::eRunItem},
        {"��������� ������ ���� �����", '2', OptionAction::eRunItem, kind_to_str(UnitKind::eCompany)},
        {"��������� ������ ������", '3', OptionAction::eRunItem, kind_to_str(UnitKind::eDepartament) },
        {"��������� ������ ����������", '4', OptionAction::eRunItem, kind_to_str(UnitKind::eEmployer) },
        {"���������� ��������� �����", '5', OptionAction::eRunItem},
    };
    m_options.insert(options.begin(), options.end());
}

void MainMenu::runOption(const Option& opt)
{
    switch (opt.m_keyCode) {
    case '1':
        m_mainUtil->loadDataFromDir();
        break;
    case '2':
        taskToCompany(opt);
        break;
    case '3':
        {
            ChoiceDeptMenu choiceDeptMenu(m_mainUtil, m_mainUtil->getCompany().name());
            choiceDeptMenu.run();
    
            std::string caption = opt.m_additionalParam;
            caption.append(" '");
            caption.append(m_mainUtil->getCompany().name());
            caption.append("'");
            ChoiceJobMenu choiceMenu(m_mainUtil, opt.m_additionalParam);
            choiceMenu.run();
        }
        break;
    case '4':
        {
            ChoiceJobMenu choiceMenu(m_mainUtil, opt.m_additionalParam);
            choiceMenu.run();
        }
        break;
    case '5':
        m_mainUtil->showLastReport();
        std::cout << "��� ����������� ������� ����� �������\n";
        get_code();
        break;
    default:
        assert(!"�������������� �����");
    };
}

void MainMenu::taskToCompany(const MenuBase::Option & opt) {
    std::string caption = opt.m_additionalParam;
    caption.append(" '");
    caption.append(m_mainUtil->getCompany().name());
    caption.append("'");
    ChoiceJobMenu choiceMenu(m_mainUtil, caption);
    choiceMenu.run();
    const std::string& resultStr = choiceMenu.resultString();
    if (resultStr.empty()) {
        std::cout << std::endl << "������ �� �������. ������� ����� "
            "������ ��� �������� � ������� ����\n";
        get_code();
        return;
    }
    m_mainUtil->doJob(str_to_job(resultStr), &m_mainUtil->getCompany());
    std::cout << "������ �� ���������� ����� '" << resultStr
        << "' ��������� �� ���������� ����� '" << m_mainUtil->getCompany().name()
        << "'\n��� �������� � ������� ���� ������� ����� ������."
        << "\n� ������� ���� ����� ����������� �����.";
    get_code();
}
