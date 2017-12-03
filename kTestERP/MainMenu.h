#pragma once

#include "BaseMenu.h"

class IUnit;

class MainMenu :
    public BaseMenu
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
};

