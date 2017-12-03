/**
\file
\brief ���������� ���� ������ ������.
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include "CustomMenu.h"

/// ���� ������ ������. ��������� ������� ���� �� ����� ����� ��� ���������� �� ������.
class ChoiceJobMenu :
    public CustomMenu
{
public:
    /**
    \brief ������� ����.
    \param[in] mainUtil ��������� �� ������� �������.
    \param[in] unitName ��� ����������� �������, ��� ������� ���������� ������.
    */
    ChoiceJobMenu(MainUtil* mainUtil, const std::string& unitName);
protected:
    virtual void runOption(const CustomMenu::Option &);
};

