/**
\file
\brief ���������� �������� ������ ��� �������� ���� � ���� �������
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include "CustomMenu.h"
#include "Company.h"

/// ������� ����� �������� ���� � ���� �������.
class BaseMenu :
    public CustomMenu {
public:
    BaseMenu(MainUtil* mainUtil, const std::string& caption);

protected:
    /**
        \brief ����� ������� - ��������� ������� ����� ��� ���������� �����
        � ��������� ������.

        \details ������� ���� ������ ������ �� ����, ��� ���� � �����.
        ��������� �������� ����� ����� �������� ��� ������ ����, � ������� ����
        ���� �� ���� ���������. � �������, ���� ����� �� ������ - ���������� ������ Ptr.
        ���� ������� ����� ����� (������ 9) ������ ����� ������� ���������� �������� ������.

        \param[in] onlyWithEmployers �������� ������ ������ � ������������.
        \return ���������� ��������� ����� ��� ������ Ptr
    */
    DepartamentPtr choiceDepartament(bool onlyWithEmployers) const;

    /**
    \brief ����� ������� - ��������� ������� ���������� ��� ���������� �����
    � ��������� ������.

    \details ������� ���� ������ ���������� ���������� ������,
    ���� ����������� ����� �����, �� �������� ������ ����� ������� ������ ����������.

    \param[in] dept �����, ����������� �������� ���� ��������
    */
    EmployerPtr choiceEmployer(Departament* dept) const;
};

