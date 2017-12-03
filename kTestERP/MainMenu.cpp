#include "stdafx.h"
#include "MainMenu.h"
#include "MainUtil.h"
#include "ChoiceJobMenu.h"
#include "ReportMenu.h"


MainMenu::MainMenu(MainUtil* mainUtil) :
    BaseMenu(mainUtil, "Главное меню")
{
    Options options = {
        {"Загрузить csv-файлы", '1', OptionAction::eRunItem},
        {"Поставить задачу всей фирме", '2', OptionAction::eRunItem, kind_to_str(UnitKind::eCompany)},
        {"Поставить задачу отделу", '3', OptionAction::eRunItem, kind_to_str(UnitKind::eDepartament) },
        {"Поставить задачу сотруднику", '4', OptionAction::eRunItem, kind_to_str(UnitKind::eEmployer) },
        {"Просмотр отчетов", '5', OptionAction::eRunItem},
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
        reporting();
        //m_mainUtil->showLastReport();
        //std::cout << "Для продолжения нажмите любую клавишу\n";
        //get_code();
        break;
    default:
        assert(!"Необработанная опция");
    };
}

void MainMenu::taskToCompany(const CustomMenu::Option & opt) {
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

void MainMenu::taskToDepartament(const CustomMenu::Option & opt)
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

void MainMenu::taskToEmployer(const CustomMenu::Option& opt)
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

void MainMenu::reporting() {
    ReportMenu reportMenu(m_mainUtil,
                          "Просмотр отчетам по структурным единицам и сотрудникам");
    reportMenu.run();
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
