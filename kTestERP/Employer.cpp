#include "stdafx.h"

#include <iostream>

#include "Employer.h"


Employer::Employer(const std::wstring& name,
                   EmployerPosition position) noexcept :
    m_name(name), m_position(position) {
    m_jobs = { Job::eVacation, Job::eCleaning };
}

bool Employer::canJob(Job job) const noexcept {
    return (m_jobs.find(job) != m_jobs.end());
}

const std::wstring& Employer::name() const noexcept {
    return m_name;
}
EmployerPosition Employer::position() const noexcept {
    return m_position;
}
const IEmployer::Jobs& Employer::jobs() const noexcept {
    return m_jobs;
}


IEmployerPtr EmployerFactory::createEmployer(const std::wstring& name,
                                             const std::wstring& positionAsText) {
    if (!name.empty()) {
        EmployerPosition pos = textToPosition(positionAsText);
        switch (pos) {
        case EmployerPosition::eProgrammer:
            return std::make_shared<Programmer>(name);
        case EmployerPosition::eWriter:
            return std::make_shared<Writer>(name);
        case EmployerPosition::eTester:
            return std::make_shared<Tester>(name);
        case EmployerPosition::eAccountant:
            return std::make_shared<Accountant>(name);
        default:
            if (m_verbose) {
                std::wcout << L"Неизвестное название специальности: "
                          << positionAsText << std::endl;
            }
            break;
        }
    }

    return nullptr;
}

EmployerPosition EmployerFactory::textToPosition(const std::wstring& positionAsText)
{
    using EmplPosMap = std::unordered_map<std::wstring, EmployerPosition>;
    static const EmplPosMap emplMap = {
        { L"Разработчик", EmployerPosition::eProgrammer },
        { L"Писатель", EmployerPosition::eWriter },
        { L"Тестер", EmployerPosition::eTester },
        { L"Писатель", EmployerPosition::eAccountant },
    };
    EmployerPosition pos = EmployerPosition::eUnknown;
    auto it = emplMap.find(positionAsText);
    if (it != emplMap.end()) {
        pos = it->second;
    }
    return pos;
}
