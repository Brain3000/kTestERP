#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <assert.h>

#include "Employer.h"

using Employers = std::list<EmployerPtr>;

class Departament : public UnitWChildrenImpl<Employer, Employers> {
public:
    Departament(std::string name) :
        UnitWChildrenImpl(name){}
    bool addEmployer(EmployerPtr employer);
protected:
    virtual EmployerPtr child(Employers::const_iterator it) const noexcept;
};
