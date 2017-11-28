#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <assert.h>

#include "Employer.h"

class Departament : public UnitImpl<UnitKind::eDepartament>{
    struct EmployerEqual : std::unary_function<IEmployer*, bool> {
        EmployerEqual(const IUnit* val) : m_val(static_cast<const IEmployer*>(val)) {}
        bool operator()(IUnitPtr u) const {
            IEmployer* e = static_cast<IEmployer*>(u.get());
            return (e->name() == m_val->name() && m_val->position() == e->position());
        }
        const IEmployer* m_val;
    };

public:
    explicit Departament(std::string name) :
        UnitImpl(name) {}
    bool addEmployer(IEmployerPtr employer);
};

using Departaments = std::unordered_map<std::string, Departament>;
