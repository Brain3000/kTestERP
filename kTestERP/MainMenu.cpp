#include "stdafx.h"
#include "MainMenu.h"
#include "ChoiceJobMenu.h"
#include "MainUtil.h"

MainMenu::MainMenu(MainUtil* mainUtil) :
    MenuBase(mainUtil, "Главное меню")
{
    m_options = {
        {"Загрузить csv-файлы", '1', OptionAction::eRunItem},
        {"Поставить задачу всей фирме", '2', OptionAction::eRunItem},
        {"Поставить задачу отделу", '3', OptionAction::eRunItem},
        {"Поставить задачу сотруднику", '4', OptionAction::eRunItem},
        {"Посмотреть последний отчет", '5', OptionAction::eRunItem},
    };
}

void MainMenu::runOption(const Option& opt) const
{
    switch (opt.m_keyCode) {
    case '1':
        m_mainUtil->loadDataFromDir();
        break;
    case '2':
    case '3':
    case '4':
        break;
    default:
        assert(!"Необработанная опция");
    };
}
