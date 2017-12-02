#pragma once

#include <set>

#include "Employer.h"

struct EmployerLess : std::binary_function<EmployerPtr, EmployerPtr, bool> {
    bool operator()(EmployerPtr e1, EmployerPtr e2) const {
        return (e1->name() < e2->name() && e1->position() < e2->position());
    }
};
using Employers = std::set<EmployerPtr, EmployerLess>;

class Departament : public UnitWChildrenImpl<Employer, Employers, UnitKind::eDepartament> {
public:
    Departament(std::string name) :
        UnitWChildrenImpl(name){}
    bool addEmployer(EmployerPtr employer);
protected:
    virtual EmployerPtr child(Employers::const_iterator it) const noexcept;
};
