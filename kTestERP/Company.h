#pragma once

#include <unordered_map>

#include "Departament.h"

using DepartamentPtr = std::shared_ptr<Departament>;
using Departaments = std::unordered_map<std::string, DepartamentPtr>;

class Company : public UnitWChildrenImpl<Departament, Departaments, UnitKind::eCompany>
{
public:
    Company() : UnitWChildrenImpl("Наша фирма"){}
    DepartamentPtr getOrCreateDept(const std::string& deptName);

protected:
    DepartamentPtr child(Departaments::const_iterator it) const noexcept;
};

