#include "stdafx.h"
#include <iostream>

#include "ChoiceJobMenu.h"
#include "Job.h"
#include "EnumImpl.h"

ChoiceJobMenu::ChoiceJobMenu(MainUtil* mainUtil, const std::string& unitName) :
    MenuBase(mainUtil, "Выберете поставленную задачу для" + unitName)
{
    //m_options = {

    //};
    for (Job e : EnumImpl<Job, Job::eProgramming, Job::eCleaning>())
    {
        std::cout << job_to_str(e) << std::endl;
    }
}
