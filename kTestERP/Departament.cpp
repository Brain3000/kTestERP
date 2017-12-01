#include "stdafx.h"

#include <algorithm>

#include <assert.h>

#include "Departament.h"

bool Departament::addEmployer(EmployerPtr employer) {
    assert(employer);
    if (m_children.find(employer) != m_children.end()) {
        return false;
    }
    m_children.insert(employer);
    return true;
}

EmployerPtr Departament::child(Employers::const_iterator it) const noexcept {
    return *it;
}
