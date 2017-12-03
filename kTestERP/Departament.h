/**
\file
\brief ���������� ������ ������
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include <set>

#include "Employer.h"

/**
\brief ������� ��� ��������� ����������� � ������ ������ ������.
���������� ������������ �� ����� � ���������. � ���������� ���.
*/
struct EmployerLess : std::binary_function<EmployerPtr, EmployerPtr, bool> {
    bool operator()(EmployerPtr e1, EmployerPtr e2) const {
        int cmpRes = e1->name().compare(e2->name());
        if (!cmpRes)
            return e1->position() < e2->position();
        return (cmpRes < 0);
    }
};
using Employers = std::set<EmployerPtr, EmployerLess>;

// ���������� ����� ������.
class Departament : public UnitWChildrenImpl<Employer, Employers, UnitKind::eDepartament> {
public:
    /// ��������� ����� � ��������� ������.
    Departament(std::string name) :
        UnitWChildrenImpl(name){}
    /**
    \brief �������� ���������� � �����.
    �������� �������� ���������� � �����. ���� ��������� � ����� ������ � ���������� ��� ���� � ������
    �� ����� ��������� �� ����� ��������.
    \param[in] employer ���������, �������� ���������� ��������.
    \return � ������ ��������� ���������� ���������� true.
    */
    bool addEmployer(EmployerPtr employer);
    /**
    \brief ���������� �� ��������� ���������� ����������.
    
    \details ��� ���� ������, ��� ���������� ������ � ������������� ����� *it �����
    �� ���������. �������� ���� *it - ��� std::pair
    */
    virtual EmployerPtr child(Employers::const_iterator it) const noexcept;

    /// ���������� �������� ������. � ������ ���������� ��� ������ ���������� �����.
    std::string description() const;
};
