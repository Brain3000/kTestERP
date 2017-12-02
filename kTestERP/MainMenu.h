#pragma once
#include "MenuBase.h"

class MainMenu :
    public MenuBase
{
public:
    MainMenu(MainUtil* mainUtil);

protected:
    virtual void runOption(const Option& opt) const;
};

