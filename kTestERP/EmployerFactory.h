/**
\file
\brief ������� �����������
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include "Employer.h"

/// ������� ���������� � ��������� ���������� � ������.
class EmployerFactory {
public:
    EmployerFactory(bool verbose) noexcept : m_verbose(verbose)
    {}
    /**
    \brief �������� ����������. 
    ������� ���������� � ��������� �������� � ��������� �������������,
    ���������� � ��������� ����. ���� ��� ������ ��� ����� ������������� ���,
    �� ������������ ������ Ptr.
    \param[in] name ������� ����������, ������ ���� ��������, ����� ��������� �� ���������.
    \param[in] positionAsText ��������� ������������� ��������� ����������. 
    ���� ����� ��������� ���, �� ��������� �� ���������.
    \return �������� ��������� ��� ������ Ptr.
    */
    EmployerPtr createEmployer(const std::string& name,
        const std::string& positionAsText);

private:
    /// ���� ������ ���������� ��������� ��� ��������.
    bool m_verbose;
};
