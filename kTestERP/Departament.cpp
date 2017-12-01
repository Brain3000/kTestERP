#include "stdafx.h"

#include <algorithm>

#include <assert.h>

#include "Departament.h"

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
