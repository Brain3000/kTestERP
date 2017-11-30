#include "stdafx.h"

#include "Company.h"

DepartamentPtr Company::getOrCreateDept(const std::string& deptName)
{
    auto it = std::find_if(m_children.begin(), m_children.end(),
        [deptName](auto dep) { return dep->name() == deptName;  });
    if (it != m_children.end())
        return *it;
    DepartamentPtr newDept = std::make_shared<Departament>(deptName, this);
    return newDept;
}

void Company::addChildReport(const std::string& report) {
    m_report.push_back(report);
}
