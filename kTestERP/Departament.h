#pragma once

#include <string>
#include <memory>
#include <unordered_map>
//#include <unordered_set>
#include <list>
#include <assert.h>

#include "Employer.h"

class Departament {
public:
    explicit Departament(std::string name) noexcept :
        m_name(name) {}
    bool addEmployer(IEmployerPtr employer);
    EmployersList&& getEmployers(EmployerPosition position) const;
    const std::string& name() const
        { return m_name;  }
    const EmployersList& getAllEmployers() const noexcept
        { return m_employers; }

private:
    const std::string m_name;
    EmployersList m_employers;
};

using Departaments = std::unordered_map<std::string, Departament>;
