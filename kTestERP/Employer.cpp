#include "stdafx.h"

#include <iostream>

#include "Employer.h"
#include "Departament.h"

bool Employer::doJob(Job job) {
    bool jobResult = m_jobs.find(job) != m_jobs.end();
    // ����� ������ ���� ������
    assert(m_report.empty());
    m_report.emplace_back(name() + " ������ " +
        (jobResult ? "��������" : "�� ����� ���������"));
    assert(m_parent);
    if (m_parent) {
        m_parent->addChildReport(m_report.back());
    }
    return jobResult;
}


EmployerPtr EmployerFactory::createEmployer(const std::string& name,
                                            const std::string& positionAsText,
                                            Departament* parent) {
    if (!name.empty()) {
        EmployerPosition pos = textToPosition(positionAsText);
        switch (pos) {
        case EmployerPosition::eProgrammer:
            return std::make_shared<Programmer>(name, parent);
        case EmployerPosition::eWriter:
            return std::make_shared<Writer>(name, parent);
        case EmployerPosition::eTester:
            return std::make_shared<Tester>(name, parent);
        case EmployerPosition::eAccountant:
            return std::make_shared<Accountant>(name, parent);
        default:
            if (m_verbose) {
                std::cout << "����������� �������� �������������: '"
                          << positionAsText << "'\n";
            }
            break;
        }
    }
    else if (m_verbose)
    {
        std::cout << "������� ������ ������� ����������, ������ ���������� ������ ��������\n";
    }

    return nullptr;
}

EmployerPosition EmployerFactory::textToPosition(const std::string& positionAsText)
{
    using EmplPosMap = std::unordered_map<std::string, EmployerPosition>;
    static const EmplPosMap emplMap = {
        { "�����������", EmployerPosition::eProgrammer },
        { "��������", EmployerPosition::eWriter },
        { "������", EmployerPosition::eTester },
        { "���������", EmployerPosition::eAccountant },
    };
    EmployerPosition pos = EmployerPosition::eUnknown;
    auto it = emplMap.find(positionAsText);
    if (it != emplMap.end()) {
        pos = it->second;
    }
    return pos;
}
