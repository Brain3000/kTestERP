#pragma once

#include "CustomMenu.h"

class ChoiceJobMenu :
    public CustomMenu
{
public:
    ChoiceJobMenu(MainUtil* mainUtil, const std::string& unitName);
protected:
    virtual void runOption(const CustomMenu::Option &);
};

