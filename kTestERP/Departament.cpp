#include "stdafx.h"

#include <algorithm>

#include <assert.h>

#include "Departament.h"

bool Departament::addEmployer(IEmployerPtr employer) {
    assert(employer);
    if (std::find_if(m_employers.begin(),
                     m_employers.end(),
                     EmployerEqual(employer)) != m_employers.end()) {
        return false;
    }
    m_employers.push_back(employer);
    return true;
}

EmployersList&& Departament::getEmployers(EmployerPosition position) const {
    EmployersList employers;
    std::copy_if(m_employers.begin(),
        m_employers.end(),
        std::back_inserter(employers),
        [position](auto emp) { return emp->position() == position; });
    return std::move(employers);
}
