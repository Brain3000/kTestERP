#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <assert.h>

#include "Employer.h"

class Departament : public UnitWChildrenImpl<Employer> {
    struct EmployerEqual : std::unary_function<EmployerPtr, bool> {
        EmployerEqual(const EmployerPtr val) : m_empl(val) {}
        bool operator()(EmployerPtr e) const {
            return (e->name() == m_empl->name() && m_empl->position() == e->position());
        }
        const EmployerPtr m_empl;
    };

public:
    Departament(std::string name) :
        UnitWChildrenImpl(name){}
    bool addEmployer(EmployerPtr employer);
};
