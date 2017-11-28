#include "stdafx.h"

#include <algorithm>

#include <assert.h>

#include "Departament.h"

bool Departament::addEmployer(IEmployerPtr employer) {
    assert(employer);
    if (std::find_if(m_childs.begin(),
                     m_childs.end(),
                     EmployerEqual(static_cast<IEmployer*>(employer.get()))) != m_childs.end()) {
        return false;
    }
    m_childs.push_back(employer);
    return true;
}

//EmployersList&& Departament::getEmployers(EmployerPosition position) const {
//    EmployersList employers;
//    std::copy_if(m_employers.begin(),
//        m_employers.end(),
//        std::back_inserter(employers),
//        [position](auto emp) { return emp->position() == position; });
//    return std::move(employers);
//}
