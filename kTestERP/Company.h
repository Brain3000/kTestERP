/**
\file
\brief ���������� ������ ��������
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include <unordered_map>

#include "Departament.h"

using DepartamentPtr = std::shared_ptr<Departament>;
using Departaments = std::unordered_map<std::string, DepartamentPtr>;

/// ���������� ������ ��� ��������
class Company : public UnitWChildrenImpl<Departament, Departaments, UnitKind::eCompany>
{
public:
    /// ������� �������� � ��������� ������.
    Company() : UnitWChildrenImpl("���� �����"){}
    /**
    \brief ������� �/��� ���������� ����� � ��������� ������.
    
    ���������� ����� � ������, ������� ��������, ���� ������ ������
    ���, �� ������� ��� ������ (��� �����������) � ����������.
    */
    DepartamentPtr getOrCreateDept(const std::string& deptName);

    /// ���������� �� ��������� �����.
    DepartamentPtr child(Departaments::const_iterator it) const noexcept;
};

