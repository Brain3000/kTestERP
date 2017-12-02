#pragma once
#include "MenuBase.h"
class ChoiceJobMenu :
    public MenuBase
{
public:
    ChoiceJobMenu(MainUtil* mainUtil, const std::string& unitName);
protected:
    void runOption(const MenuBase::Option &) const {}
};

