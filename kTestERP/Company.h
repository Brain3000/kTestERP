#pragma once

#include "Departament.h"
#include "ERPException.h"

class Company
{
public:
    Departament& getOrCreateDept(const std::string& deptName);

private:
    Departaments m_depts;
};

