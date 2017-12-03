#pragma once

#include "CustomMenu.h"
#include "Company.h"

class BaseMenu :
    public CustomMenu {
public:
    BaseMenu(MainUtil* mainUtil, const std::string& caption);

protected:
    DepartamentPtr choiceDepartament(bool onlyWithEmployers) const;
    EmployerPtr choiceEmployer(Departament* dept) const;
};

