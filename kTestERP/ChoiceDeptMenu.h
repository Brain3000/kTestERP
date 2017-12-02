#pragma once
#include "MenuBase.h"

class ChoiceDeptMenu :
    public MenuBase {
public:
    ChoiceDeptMenu(MainUtil* mainUtil, const std::string& caption);

protected:
    virtual void runOption(const MenuBase::Option& opt);
};