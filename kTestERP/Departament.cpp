#include "stdafx.h"

#include <algorithm>

#include <assert.h>

#include "Departament.h"
#include "Company.h"

bool Departament::addEmployer(EmployerPtr employer) {
    assert(employer);
    if (std::find_if(m_children.begin(),
                     m_children.end(),
                     EmployerEqual(employer)) != m_children.end()) {
        return false;
    }
    m_children.push_back(employer);
    return true;
}

void Departament::addChildReport(const std::string& record) {
    m_report.push_back(record);
    assert(m_parent);
    if (m_parent)
        m_parent->addChildReport(m_name + "->" + record);
}

//EmployersList&& Departament::getEmployers(EmployerPosition position) const {
//    EmployersList employers;
//    std::copy_if(m_employers.begin(),
//        m_employers.end(),
//        std::back_inserter(employers),
//        [position](auto emp) { return emp->position() == position; });
//    return std::move(employers);
//}
