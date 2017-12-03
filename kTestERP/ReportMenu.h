/**
\file
\brief Меню отчетов
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/

#pragma once
#include "BaseMenu.h"

class MainUtil;

/// Меню отчетов
class ReportMenu :
    public BaseMenu
{
public:
    /// Конструктор, генерирует пункты меню.
    ReportMenu(MainUtil* mainUtil, const std::string& caption);

private:
    /// Обработка опций меню
    virtual void runOption(const Option& opt);
    /// Выводит отчет по компании
    void companyReport(const CustomMenu::Option& opt);
    /// Позволяет выбрать отдел и выводит по нему отчет.
    void departamentReport(const CustomMenu::Option& opt);
    /// Позволяет выбрать отдел, сотрудника и вывести по нему отчет.
    void employerReport(const CustomMenu::Option& opt);
};

