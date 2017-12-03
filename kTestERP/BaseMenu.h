/**
\file
\brief Реализация базового класса для главного меню и меню отчетов
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include "CustomMenu.h"
#include "Company.h"

/// Базовый класс главного меню и меню отчетов.
class BaseMenu :
    public CustomMenu {
public:
    BaseMenu(MainUtil* mainUtil, const std::string& caption);

protected:
    /**
        \brief Общая функция - позволяет выбрать отдел для назначения работ
        и получения отчета.

        \details Создает меню выбора отдела из всех, что есть в фирме.
        Позволяет выбирать между всеми отделами или только теми, в которых есть
        хотя бы один сотрудник. В случает, если отдел не выбран - возвращает пустой Ptr.
        Если отделов очень много (больше 9) список можно листать циклически клавишей Пробел.

        \param[in] onlyWithEmployers выбирать только отделы с сотрудниками.
        \return возвращает выбранный отдел или пустой Ptr
    */
    DepartamentPtr choiceDepartament(bool onlyWithEmployers) const;

    /**
    \brief Общая функция - позволяет выбрать сотрудника для назначения работ
    и получения отчета.

    \details Создает меню выбора сотрудника указанного отдела,
    если сотрудников очень много, то клавишей Пробел можно листать список циклически.

    \param[in] dept отдел, сотрудников которого надо отбирать
    */
    EmployerPtr choiceEmployer(Departament* dept) const;
};

