#include "stdafx.h"

#include "EmployerFactory.h"

EmployerPtr EmployerFactory::createEmployer(const std::string& name,
    const std::string& positionAsText) {
    EmployerPtr employer;
    if (!name.empty()) {
        try {
            // str_to_pos может стрельнуть std::out_of_range
            EmployerPosition pos = str_to_pos(positionAsText);
            switch (pos) {
            case EmployerPosition::eProgrammer:
                employer = std::make_shared<Programmer>(name);
                break;
            case EmployerPosition::eWriter:
                employer = std::make_shared<Writer>(name);
                break;
            case EmployerPosition::eTester:
                employer = std::make_shared<Tester>(name);
                break;
            case EmployerPosition::eAccountant:
                employer = std::make_shared<Accountant>(name);
                break;
            default:
                if (m_verbose) {
                    std::cout << "Неизвестное название специальности: '"
                        << positionAsText << "'\n";
                }
                break;
            }
        }
        catch (const std::out_of_range&) {
            // Просто задавим исключение,
            // и Employer останется пустым
        }
    }
    else if (m_verbose)
    {
        std::cout << "Указано пустая фамилия сотрудника, такого сотрудника нельзя добавить\n";
    }

    return employer;
}
