#include "stdafx.h"

#include <iostream>

#include "Employer.h"

bool Employer::doJob(Job job, StringList& report) const {
    bool jobResult = m_jobs.find(job) != m_jobs.end();
    std::string msg = m_name;
    msg.append(" работу ");
    msg.append(jobResult ? "выполнил(а)" : "не может выполнить");
    report.emplace_back(msg);
    return jobResult;
}


EmployerPtr EmployerFactory::createEmployer(const std::string& name,
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
                std::cout << "Неизвестное название специальности: '"
                          << positionAsText << "'\n";
            }
            break;
        }
    }
    else if (m_verbose)
    {
        std::cout << "Указано пустая фамилия сотрудника, такого сотрудника нельзя добавить\n";
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
        { "Бухгалтер", EmployerPosition::eAccountant },
    };
    EmployerPosition pos = EmployerPosition::eUnknown;
    auto it = emplMap.find(positionAsText);
    if (it != emplMap.end()) {
        pos = it->second;
    }
    return pos;
}
