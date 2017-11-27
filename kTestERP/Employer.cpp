#include "stdafx.h"

#include <iostream>

#include "Employer.h"


Employer::Employer(const std::string& name,
                   EmployerPosition position) noexcept :
    m_name(name), m_position(position) {
    m_jobs = { Job::eVacation, Job::eCleaning };
}

bool Employer::canJob(Job job) const noexcept {
    return (m_jobs.find(job) != m_jobs.end());
}

const std::string& Employer::name() const noexcept {
    return m_name;
}
EmployerPosition Employer::position() const noexcept {
    return m_position;
}
const IEmployer::Jobs& Employer::jobs() const noexcept {
    return m_jobs;
}


IEmployerPtr EmployerFactory::createEmployer(const std::string& name,
                                             const std::string& positionAsText) {
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
                std::cout << "Неизвестное название специальности: "
                          << positionAsText << std::endl;
            }
            break;
        }
    }

    return nullptr;
}

EmployerPosition EmployerFactory::textToPosition(const std::string& positionAsText)
{
    using EmplPosMap = std::unordered_map<std::string, EmployerPosition>;
    static const EmplPosMap emplMap = {
        { "Разработчик", EmployerPosition::eProgrammer },
        { "Писатель", EmployerPosition::eWriter },
        { "Тестер", EmployerPosition::eTester },
        { "Писатель", EmployerPosition::eAccountant },
    };
    EmployerPosition pos = EmployerPosition::eUnknown;
    auto it = emplMap.find(positionAsText);
    if (it != emplMap.end()) {
        pos = it->second;
    }
    return pos;
}
