#include "stdafx.h"
#include <iostream>

#include "ChoiceJobMenu.h"
#include "Job.h"
#include "EnumImpl.h"

ChoiceJobMenu::ChoiceJobMenu(MainUtil* mainUtil, const std::string& unitName) :
    MenuBase(mainUtil, "Выберите задачу для постановки " + unitName)
{
    uint8_t initKeyCode = '1';

    for (Job e : EnumImpl<Job>())
    {
        std::cout << job_to_str(e) << std::endl;
        m_options.emplace(job_to_str(e), initKeyCode++, OptionAction::eRunItemAndExit, job_to_str(e));
    }
}

void ChoiceJobMenu::runOption(const MenuBase::Option& opt) {
    m_resultString = opt.m_additionalParam;
}
