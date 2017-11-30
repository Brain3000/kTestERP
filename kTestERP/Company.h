#pragma once

#include "Departament.h"

using DepartamentPtr = std::shared_ptr<Departament>;

class Company : public UnitWChildrenImpl<UnitKind::eCompany, Departament>
{
public:
    Company() : UnitWChildrenImpl("Наша фирма"){}
    DepartamentPtr getOrCreateDept(const std::string& deptName);
    void addChildReport(const std::string& report);
};

