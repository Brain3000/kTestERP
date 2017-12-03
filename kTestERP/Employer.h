/**
\file
\brief ���������� �������� ��������� � ������������� ���������.
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <assert.h>

#include "UnitImpl.h"

/// ���� ���������� �����������.
enum class EmployerPosition {
    eProgrammer,    ///< �����������
    eWriter,        ///< ����������� ��������
    eTester,        ///< ���������� ������������
    eAccountant,    ///< ���������

    eFirst = eProgrammer,   ///< ������ � ��������� �������� ������������ ��� ������������
    eLast = eAccountant,
};

/// ���������� �� ��������� � ��������� �������������.
const std::string& pos_to_str(EmployerPosition pos);

/// �� ���������� ������������� ���������� ������������ ��� ���������.
/// � ������, ���� �� ���������� ������������� ������������ �� ����������,
/// �������� std::out_of_range
EmployerPosition str_to_pos(const std::string& posAsStr);

/// ���������� ������ ��� ����������
class Employer : public UnitImpl {

public:
    /// ���������� ���������
    virtual EmployerPosition position() const noexcept
        { return m_position; }
    /// ���������� ������ �����, ������� ����� ���������
    /// ��������� (�� ������ ���������)
    virtual const Jobs& jobs() const noexcept
        { return m_jobs; }

// IUnit
public:
    /**
        \brief ��������� ������
        \param[in] job - ��� ������
        \param[out] report - ����� � ���������� ������
        \return � ������, ���� ��������� ����� ��������� ������ �������
        ���� - ���������� true
    */    
    virtual bool doJob(Job job, StringList& report);

    /// ���������� ����� � ������ ������ ������� ����������
    /// ��� ����� �� ��������� ������
    virtual const std::string& report() const noexcept;

public:
    /**
    \brief �����������. ���������� ��� � ���������.
    \param[in] ������� ����������
    \param[in] ���������� ���������
    */
    Employer(const std::string& name, EmployerPosition position);

protected:
    Jobs m_jobs; /// ������ �����, ������� ��������� ����� �������

private:
    EmployerPosition m_position; /// ���������
    std::string m_emptyReport;   /// ����� ������, ������� ������������,
                                 /// ���� ������� ������ �� �������������.
};

using EmployerPtr = std::shared_ptr<Employer>;

/**
    \brief ��������� ����� ��� ���������� ���������� �����������
    �� ������ ���������� � ������ ������� ����������� �����.

    \details � ���������� ������� ���������� ��������� � ������
    �����, ������ �� ����� ���������.
*/
template<EmployerPosition P, Job... jobs>
class EmployerImpl : public Employer {
public:
    EmployerImpl(const std::string& name) :
        Employer(name, P) {
            m_jobs = { { jobs... } };
            /// �� ��� ���������� ����������� ����� ������ "������" � "������ �������� �����".
            m_jobs.insert(Job::eCleaning);
            m_jobs.insert(Job::eVacation);
    }
};

/// ����������� (����� ��������������� � �������������).
using Programmer = EmployerImpl<EmployerPosition::eProgrammer, Job::eProgramming, Job::eProjecting>;
/// ������ (����� ����������).
using Writer = EmployerImpl<EmployerPosition::eWriter, Job::eTranslation>;
/// ����������� (����� ����������� � ���������� ���� ������������)
using Tester = EmployerImpl<EmployerPosition::eTester, Job::eTesting, Job::ePlaningTest>;
/// ��������� (����� ��������� �������� � ������ �����)
using Accountant = EmployerImpl<EmployerPosition::eAccountant, Job::ePaySallory, Job::eReporting>;


