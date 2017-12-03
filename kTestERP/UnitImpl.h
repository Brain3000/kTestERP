/**
\file
\brief ������� ���������� ��� ���� ����������� ������
� ��� ����������� ������ � ������������ ���������.
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include <memory>
#include <algorithm>

#include "IUnit.h"

/// ����� ���������� ������� ������������� �� ���� �����.
const std::string& kind_to_str(UnitKind kind);

/**
    \braef ������� ���������� ���� ������.
    ��� ����������� ����������� ������ � ����� ������.
    ������, ������������� m_report ��� ���������, ��������� 
    ������ ��������� � ������, ������� ����� ����������� ��������
    � �� ����� �� � ������, ���� ������ �� ����������� ������.
    (������ ����� �� ����������, ��������� ����� �� ����� �������
    ���� ��� ����� ��� ��� ����������� ���������).
*/
class UnitImpl : public IUnit {
public:
    UnitImpl(const std::string& name, UnitKind kind) : m_name(name), m_kind(kind)
    {}
    /// ���������� ��� ����������� �������.
    virtual const std::string& name() const noexcept {
        return m_name;
    }

    /// ���������� ��� ����������� �������.
    virtual UnitKind kind() const noexcept {
        return m_kind;
    }

protected:
    std::string m_name;
    UnitKind m_kind;
    std::string m_report;
};

/**
    \brief ������� ���������� ��� ����������� �������������, ������� 
    ����� ��������� � ���� ������ ����������� �������������.
    U - ��� ������������ ������������ �������������
    C - ��� ����������, � ������� ����� �������� ����������� ��������
    K - ��� ������� ������������ �������������
*/
template<typename U, typename C, UnitKind K>
class UnitWChildrenImpl : public UnitImpl {
public:
    using ChildPtr = std::shared_ptr<U>;
    using Children = C;
    using Iterator = typename C::const_iterator;

    /// �����������. ���������� ���, ��� ������� �� �������.
    UnitWChildrenImpl(const std::string& name);

    /**
    \brief �������� ���������� ������ "���������������" ���
    ������������ ������������� � ������������
    \param[in] job - ��� ������
    \param[out] report - ����� � ���������� ������
    \return � ������, ���� ��������� ����� ��������� ������ �������
    ���� - ���������� true
    */
    virtual bool doJob(Job job, StringList& report);

    /// �������� ��������� � ������������ ����������
    const Children& getChildren() const noexcept {
        return m_children;
    }

    /// �������� ����������� ������� �� ���������
    /// *it �� ��� ���� ����������� �����������.
    virtual ChildPtr child(Iterator it) const noexcept = 0;

    /// �������� ������������ �� �����.
    /// \return � ������ ������ ���������� ���������� �������.
    /// ����� - ������ ���������.
    ChildPtr childByName(const std::string& name) const noexcept;

    /// ���������� ����� � ������ ������ ������� �����.
    /// ��� ���������� � �����������.
    virtual const std::string& report() const noexcept;

protected:
    Children m_children;

private:
    std::string m_emptyReport; ///< ������ ����� - �����, ������� ������������, ���� ������� ������ �� ��������.
};

template<typename U, typename C, UnitKind K>
UnitWChildrenImpl<U, C, K>::UnitWChildrenImpl(const std::string& name) :
    UnitImpl(name, K),
    m_emptyReport("����������� ������������� " + kind_to_str(K) + " '" + name + "' ����� �����������.") {
}



template<typename U, typename C, UnitKind K>
bool UnitWChildrenImpl<U, C, K>::doJob(Job job, StringList& report) {
    std::string msg("������ '");
    msg.append(job_to_str(job));
    msg.append("' ����������� ������������� ");
    msg.append(kind_to_str(kind()));
    msg.append(" '");
    msg.append(m_name);
    msg.append("'");
    if (m_children.empty()) {
        msg.append("' ��������� �� �����, ��������� ����������� ����������� ����������� �������.");
        report.push_back(msg);
        return false;
    }

    StringList internalReport;
    bool jobResult(false);
    for (auto it = m_children.begin(); it != m_children.end(); ++it) {
        if (child(it)->doJob(job, internalReport) && !jobResult) {
            jobResult = true;
        }
    }
    msg.append(jobResult ? "' ��������(�)." : "' ��������� �� �����.");
    report.push_back(msg);
    std::swap(msg, m_report);
    std::transform(internalReport.begin(), internalReport.end(), std::back_inserter(report),
        [](std::string s) { s.insert(s.begin(), 4, ' '); return s; });
    return jobResult;
}

template<typename U, typename C, UnitKind K>
typename UnitWChildrenImpl<U, C, K>::ChildPtr
UnitWChildrenImpl<U, C, K>::childByName(const std::string& name) const noexcept {
    ChildPtr res;
    for (auto it = m_children.cbegin(); it != m_children.end(); ++it) {
        ChildPtr tmp = child(it);
        if (tmp->name() == name) {
            std::swap(res, tmp);
            break;
        }
    }
    return res;
}

template<typename U, typename C, UnitKind K>
const std::string& UnitWChildrenImpl<U, C, K>::report() const noexcept{
    return (m_report.empty() ? m_emptyReport : m_report);
}
