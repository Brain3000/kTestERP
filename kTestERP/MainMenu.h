#pragma once
#include "MenuBase.h"

class MainMenu :
    public MenuBase
{
public:
    MainMenu(MainUtil* mainUtil);

protected:
    virtual void runOption(const Option& opt);

private:
    void taskToCompany(const MenuBase::Option& opt);
    void taskToDepartament(const MenuBase::Option& opt);
    void MainMenu::taskToEmployer(const MenuBase::Option& opt);
};

