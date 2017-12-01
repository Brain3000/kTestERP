#include "stdafx.h"

#include <algorithm>

#include <assert.h>

#include "Departament.h"

bool Departament::addEmployer(EmployerPtr employer) {
    struct EmployerEqual : std::unary_function<EmployerPtr, bool> {
        EmployerEqual(const EmployerPtr val) : m_empl(val) {}
        bool operator()(EmployerPtr e) const {
            return (e->name() == m_empl->name() && m_empl->position() == e->position());
        }
        const EmployerPtr m_empl;
    };

    assert(employer);
    if (std::find_if(m_children.begin(),
                     m_children.end(),
                     EmployerEqual(employer)) != m_children.end()) {
        return false;
    }
    m_children.push_back(employer);
    return true;
}

EmployerPtr Departament::child(Employers::const_iterator it) const noexcept {
    return *it;
}
