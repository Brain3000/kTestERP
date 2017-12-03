#pragma once
#include "BaseMenu.h"

class MainUtil;

class ReportMenu :
    public BaseMenu
{
public:
    ReportMenu(MainUtil* mainUtil, const std::string& caption);

private:
    virtual void runOption(const Option& opt);
    void companyReport(const CustomMenu::Option& opt);
    void departamentReport(const CustomMenu::Option& opt);
    void employerReport(const CustomMenu::Option& opt);
};

