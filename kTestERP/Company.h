#pragma once

#include "Departament.h"

using DepartamentPtr = std::shared_ptr<Departament>;

class Company : public UnitWChildrenImpl<Departament>
{
public:
    Company() : UnitWChildrenImpl("���� �����"){}
    DepartamentPtr getOrCreateDept(const std::string& deptName);
};

