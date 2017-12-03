#include "stdafx.h"
#include "ReportMenu.h"
#include "MainUtil.h"

ReportMenu::ReportMenu(MainUtil* mainUtil, const std::string& caption):
    BaseMenu(mainUtil, caption) {
    Options options = {
        { "���������� ����� �� �����", '1', OptionAction::eRunItem, kind_to_str(UnitKind::eCompany) },
        { "���������� ����� �� ������", '2', OptionAction::eRunItem, kind_to_str(UnitKind::eDepartament) },
        { "���������� ����� �� ����������", '3', OptionAction::eRunItem, kind_to_str(UnitKind::eEmployer) },
    };
    m_options.insert(options.begin(), options.end());
}

void ReportMenu::runOption(const Option& opt)
{
    switch (opt.m_keyCode) {
    case '1':
        companyReport(opt);
        break;
    case '2':
        departamentReport(opt);
        break;
    case '3':
        employerReport(opt);
        break;
    default:
        assert(!"�������������� �����");
    };
}

void ReportMenu::companyReport(const CustomMenu::Option& opt) {
    m_mainUtil->showLastReport();
    std::cout << "��� ����������� ������� ����� �������\n";
    get_code();
}

void ReportMenu::departamentReport(const CustomMenu::Option& opt) {
    DepartamentPtr dept = choiceDepartament(false);
    if (!dept || dept->getChildren().empty()) {
        return;
    }
    system("cls");
    std::cout << "����� � ���������� �������� ������ ������������� '"
              << dept->name() << "'\n"
              << dept->report() << std::endl;
    get_code();
}

void ReportMenu::employerReport(const CustomMenu::Option& opt) {
    DepartamentPtr dept = choiceDepartament(true);

    EmployerPtr empl = choiceEmployer(dept.get());
    if (!empl) {
        return;
    }
    system("cls");
    std::cout << "����� � ���������� �������� ������ ����������� '"
        << empl->name() << "'\n"
        << empl->report() << std::endl;
    get_code();
}
