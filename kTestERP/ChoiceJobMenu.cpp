#include "stdafx.h"
#include <iostream>

#include "ChoiceJobMenu.h"
#include "Job.h"
#include "EnumImpl.h"

ChoiceJobMenu::ChoiceJobMenu(MainUtil* mainUtil, const std::string& unitName) :
    CustomMenu(mainUtil, "�������� ������ ��� ���������� ����������� �������: " + unitName)
{
    char initKeyCode = '1';

    for (Job e : EnumImpl<Job>())
    {
        std::cout << job_to_str(e) << std::endl;
        m_options.emplace(job_to_str(e), initKeyCode++, OptionAction::eRunItemAndExit, job_to_str(e));
    }
}

void ChoiceJobMenu::runOption(const CustomMenu::Option& opt) {
    m_resultString = opt.m_additionalParam;
}
