#include "stdafx.h"
#include "MainMenu.h"
#include "ChoiceJobMenu.h"
#include "ChoiceChildMenu.h"
#include "MainUtil.h"

using ChoiceDeptMenu = ChoiceChildMenu<Company>;
using ChoiceEmployerMenu = ChoiceChildMenu<Departament>;

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
        taskToDepartament(opt);
        break;
    case '4':
        taskToEmployer(opt);
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
    ChoiceJobMenu jobMenu(m_mainUtil, caption);
    jobMenu.run();
    const std::string& jobName = jobMenu.resultString();
    if (jobName.empty()) {
        return;
    }
    doJob(jobName, &m_mainUtil->getCompany());
}

void MainMenu::taskToDepartament(const MenuBase::Option & opt)
{
    DepartamentPtr dept = choiceDepartament(false);
    if (!dept) {
        return;
    }

    std::string caption = opt.m_additionalParam;
    caption.append(" '");
    caption.append(dept->name());
    caption.append("'");
    ChoiceJobMenu jobMenu(m_mainUtil, caption);
    jobMenu.run();
    const std::string& jobName = jobMenu.resultString();
    if (jobName.empty()) {
        return;
    }
    doJob(jobName, dept.get());
}

void MainMenu::taskToEmployer(const MenuBase::Option& opt)
{
    DepartamentPtr dept = choiceDepartament(true);

    EmployerPtr empl = choiceEmployer(dept.get());
    if (!empl) {
        return;
    }

    ChoiceJobMenu jobMenu(m_mainUtil, kind_to_str(empl->kind()) + " " + empl->name());
    jobMenu.run();
    const std::string& jobName = jobMenu.resultString();
    if (jobName.empty()) {
        return;
    }
    doJob(jobName, empl.get());
}

void MainMenu::doJob(const std::string& jobName, IUnit* unut) {
    m_mainUtil->doJob(str_to_job(jobName), unut);
    std::cout << "������ �� ���������� ����� '" << jobName
        << "' ��������� �� ���������� "
        << "\n��� ��������� ������ ������� 'O'."
        << "\n��� �������� � ������� ���� ������� ����� ������.";
    int code = get_code();
    if (code == 'O' || code == '�') {
        m_mainUtil->showLastReport();
        std::cout << "��� ����������� ������� ����� �������\n";
        get_code();
    }
}

DepartamentPtr MainMenu::choiceDepartament(bool onlyWithEmployers) const {
    const Company& company = m_mainUtil->getCompany();

    if (company.getChildren().empty()) {
        std::cout << "\n� �������� '" << company.name()
            << "' ��� �������. ������ ��������.\n"
            << "������� �� ����� ������� ��� �������� � ���������� ����.";
        get_code();
        return DepartamentPtr();
    }

    DepartamentPtr dept;
    do {
        ChoiceDeptMenu deptMenu(m_mainUtil, &company);
        deptMenu.run();
        dept = deptMenu.result();
        if (!dept) {
            return DepartamentPtr();
        }

        if (!dept->getChildren().empty()) {
            break;
        }
        std::cout << "\n� ������ " << " '" << dept->name()
            << "' ��� �����������. ������ ��������.\n"
            << "��������� ����� ��� �������� ����\n"
            << "������� �� ����� ������� ��� �����������.";
        get_code();
    }
    while (onlyWithEmployers);
    return dept;
}

EmployerPtr MainMenu::choiceEmployer(Departament* dept) const {
    ChoiceEmployerMenu emplMenu(m_mainUtil, dept);
    emplMenu.run();
    EmployerPtr empl = emplMenu.result();
    return empl;

}
