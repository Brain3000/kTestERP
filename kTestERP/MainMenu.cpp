#include "stdafx.h"
#include "MainMenu.h"
#include "ChoiceJobMenu.h"
#include "ChoiceChildMenu.h"
#include "MainUtil.h"

using ChoiceDeptMenu = ChoiceChildMenu<Company>;
using ChoiceEmployerMenu = ChoiceChildMenu<Departament>;

MainMenu::MainMenu(MainUtil* mainUtil) :
    MenuBase(mainUtil, "Главное меню")
{
    Options options = {
        {"Загрузить csv-файлы", '1', OptionAction::eRunItem},
        {"Поставить задачу всей фирме", '2', OptionAction::eRunItem, kind_to_str(UnitKind::eCompany)},
        {"Поставить задачу отделу", '3', OptionAction::eRunItem, kind_to_str(UnitKind::eDepartament) },
        {"Поставить задачу сотруднику", '4', OptionAction::eRunItem, kind_to_str(UnitKind::eEmployer) },
        {"Посмотреть последний отчет", '5', OptionAction::eRunItem},
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
        std::cout << "Для продолжения нажмите любую клавишу\n";
        get_code();
        break;
    default:
        assert(!"Необработанная опция");
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
    std::cout << "Приказ на выполнение работ '" << jobName
        << "' направлен на выполнение "
        << "\nДля просмотра отчета нажмите 'O'."
        << "\nДля возврата в главное меню нажмите любую кнопку.";
    int code = get_code();
    if (code == 'O' || code == 'Щ') {
        m_mainUtil->showLastReport();
        std::cout << "Для продолжения нажмите любую клавишу\n";
        get_code();
    }
}

DepartamentPtr MainMenu::choiceDepartament(bool onlyWithEmployers) const {
    const Company& company = m_mainUtil->getCompany();

    if (company.getChildren().empty()) {
        std::cout << "\nВ компании '" << company.name()
            << "' нет отделов. Нечего выбирать.\n"
            << "Нажмите на любую клавишу для возврата в предыдущее меню.";
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
        std::cout << "\nВ отделе " << " '" << dept->name()
            << "' нет сотрудников. Нечего выбирать.\n"
            << "Повторите выбор или покиньте меню\n"
            << "Нажмите на любую клавишу для продолжения.";
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
