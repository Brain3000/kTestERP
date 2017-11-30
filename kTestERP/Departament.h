#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <assert.h>

#include "Employer.h"

class Company;

class Departament : public UnitWChildrenImpl<UnitKind::eDepartament, Employer> {
    struct EmployerEqual : std::unary_function<EmployerPtr, bool> {
        EmployerEqual(const EmployerPtr val) : m_empl(val) {}
        bool operator()(EmployerPtr e) const {
            return (e->name() == m_empl->name() && m_empl->position() == e->position());
        }
        const EmployerPtr m_empl;
    };

public:
    Departament(std::string name, Company* parent) :
        UnitWChildrenImpl(name){}
    bool addEmployer(EmployerPtr employer);
    void addChildReport(const std::string& record);

private:
    Company* m_parent;
};

//using Departaments = std::unordered_map<std::string, Departament>;
