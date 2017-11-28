#include "stdafx.h"

#include "Company.h"
#include "ERPException.h"

Departament& Company::getOrCreateDept(const std::string& deptName)
{
    auto it = m_depts.find(deptName);
    if (it != m_depts.end())
        return it->second;
    auto p = m_depts.emplace(deptName, deptName);
    if (!p.second) {
        throw ERPException("Ќе удалось добавить подразделение с именем " + deptName);
    }
    return p.first->second;
}
