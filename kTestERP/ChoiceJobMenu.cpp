#include "stdafx.h"

#include "ChoiceJobMenu.h"
#include "Job.h"

ChoiceJobMenu::ChoiceJobMenu(MainUtil* mainUtil, const std::string& unitName) :
    MenuBase(mainUtil, "�������� ������������ ������ ���" + unitName)
{
    m_options = {

    };
}
