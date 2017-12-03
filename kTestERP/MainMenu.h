#pragma once
#include "MenuBase.h"

class IUnit;

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
    void taskToEmployer(const MenuBase::Option& opt);
    void doJob(const std::string& jobName, IUnit* unit);    
};

