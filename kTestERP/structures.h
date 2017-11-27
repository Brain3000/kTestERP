#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <assert.h>

#include "Employer.h"
//
//class Departament {
//public:
//    Departament(std::string name) noexcept :
//        m_name(name) {}
//    bool addEmployer(IEmployerPtr employer);
//    EmployersList&& getEmployers(EmployerPosition position) const;
//    const std::string& name() const { return m_name;  }
//private:
//    const std::string m_name;
//    EmployersMap m_employers;
//};
//
//struct DepartamentHash
//{
//    size_t operator()(const Departament& dep) const
//    {
//        return dep.name().length();
//    }
//};
//
//using Departaments = std::unordered_set<Departament, DepartamentHash>;
