#include "stdafx.h"

#include "Company.h"

DepartamentPtr Company::getOrCreateDept(const std::string& deptName) {
    auto it = m_children.find(deptName);
    if (it != m_children.end())
        return it->second;
    DepartamentPtr newDept = std::make_shared<Departament>(deptName);
    m_children.emplace(deptName, newDept);
    return newDept;
}

DepartamentPtr Company::child(Departaments::const_iterator it) const noexcept {
    return it->second;
}
