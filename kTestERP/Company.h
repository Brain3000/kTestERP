#pragma once

#include "Departament.h"

class Company
{
public:
    Departament& getOrCreateDept(const std::string& deptName);

private:
    Departaments m_depts;
};

