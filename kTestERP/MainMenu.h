#pragma once

#include "CustomMenu.h"
#include "Company.h"

class IUnit;

class MainMenu :
    public CustomMenu
{
public:
    MainMenu(MainUtil* mainUtil);

protected:
    virtual void runOption(const Option& opt);

private:
    void taskToCompany(const CustomMenu::Option& opt);
    void taskToDepartament(const CustomMenu::Option& opt);
    void taskToEmployer(const CustomMenu::Option& opt);
    void doJob(const std::string& jobName, IUnit* unit);    

    DepartamentPtr choiceDepartament(bool onlyWithEmployers) const;
    EmployerPtr choiceEmployer(Departament* dept) const;
};

