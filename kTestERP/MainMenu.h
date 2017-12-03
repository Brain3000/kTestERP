/**
\file
\brief Главное меню.
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include "BaseMenu.h"

class IUnit;
/// Главное меню.
class MainMenu :
    public BaseMenu
{
public:
    /// Конструктор, генерирует пункты меню.
    MainMenu(MainUtil* mainUtil);

private:
    /// Обработка пунктов меню.
    virtual void runOption(const Option& opt);

    /// Поставить задачу компании вцелом.
    void taskToCompany(const CustomMenu::Option& opt);
    /// Выбрать отдел и поставить ему задачу.
    void taskToDepartament(const CustomMenu::Option& opt);
    /// Выбрать отдел, сотрудника и поставить ему задачу.
    void taskToEmployer(const CustomMenu::Option& opt);
    /// Вывести отчет (фирма/отдел/сотрудник).
    void reporting();
    /// Отдать приказ на работу выбранной структурной единице.
    void doJob(const std::string& jobName, IUnit* unit);    
};

