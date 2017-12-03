/**
    \file
    \brief ����� ������� ����������� ������: ������������ ����� ������ � ����� ��������� �����.
    \author Leontyev George
    \version 1.0
    \date ������ 2017
*/
#pragma once


#include <list>
#include <string>
#include <iostream>
#include <assert.h>

#include "Job.h"

/// ������������ ����� ������������ � ���������� ������.
enum class UnitKind {
    eCompany,           ///< ��������
    eDepartament,       ///< �����
    eEmployer,          ///< ���������

    eFirst = eCompany,  ///< ������ � ��������� ������� ��� ������������ �� ������������.
    eLast = eEmployer,
};

using StringList = std::list<std::string>;

/**
    \bref ��������� ��� ���� ������: �����, ������ � ����������
    �������� ������� ����� ����� �������.
    
    ��� ����� ����� ���, ��� (�����, �����, ���������),
    ����� �������� ������ �� ���������� �����, � ����� �������� �����.
*/
class IUnit {
public:
    virtual ~IUnit() {}
    /**
    \bref ��������� � ��������� ������� �� ���������� ������.
    \param[in] job ��� �����.
    \param[out] report �����, ������������ ���������� �������,
    ���������, ����� ��������� ����� �� ������/����� ���������
    ��� ������������� ���������� ������ ��������� ����� � ���
    ������������� ����� ������� doJob �������� report
    \return � ������, ���� ���� ����� ��������� ������ ���� job
    �������
    */
    virtual bool doJob(Job job, StringList& report) = 0;

    /// ���������� ��� �����
    virtual const std::string& name() const noexcept = 0;
    /// ���������� ��� �����
    virtual UnitKind kind() const noexcept = 0;
    /// ���������� ��������� ����� �� ������� ����� ���
    /// ���������� �� ����������� ������
    virtual const std::string& report() const noexcept = 0;
};

