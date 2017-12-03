/**
\file
\brief Реализация меню выбора работы.
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include "CustomMenu.h"

/// Меню выбора работы. Позволяет выбрать одно из видов работ или отказаться от выбора.
class ChoiceJobMenu :
    public CustomMenu
{
public:
    /**
    \brief Создает меню.
    \param[in] mainUtil указатель на главную утилиту.
    \param[in] unitName имя структурной единицы, для которой выбирается работа.
    */
    ChoiceJobMenu(MainUtil* mainUtil, const std::string& unitName);
protected:
    virtual void runOption(const CustomMenu::Option &);
};

