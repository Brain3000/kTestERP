#include "stdafx.h"
#include "BaseMenu.h"

#include "ChoiceJobMenu.h"
#include "ChoiceChildMenu.h"
#include "MainUtil.h"

using ChoiceDeptMenu = ChoiceChildMenu<Company>;
using ChoiceEmployerMenu = ChoiceChildMenu<Departament>;

BaseMenu::BaseMenu(MainUtil* mainUtil, const std::string& caption):
    CustomMenu(mainUtil, caption) {
}


DepartamentPtr BaseMenu::choiceDepartament(bool onlyWithEmployers) const {
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
    } while (onlyWithEmployers);
    return dept;
}

EmployerPtr BaseMenu::choiceEmployer(Departament* dept) const {
    assert(dept);
    ChoiceEmployerMenu emplMenu(m_mainUtil, dept);
    emplMenu.run();
    EmployerPtr empl = emplMenu.result();
    return empl;

}
