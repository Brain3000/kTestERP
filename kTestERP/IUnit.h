#pragma once

#include <list>
#include <string>
#include <iostream>
#include <assert.h>

#include "Job.h"

enum class UnitKind {
    eCompany,
    eDepartament,
    eEmployer,

    eFirst = eCompany,
    eLast = eEmployer,
};

using StringList = std::list<std::string>;

class IUnit {
public:
    virtual ~IUnit() {}
    virtual bool doJob(Job job, StringList& report) const = 0;
    virtual const std::string& name() const noexcept = 0;
    virtual UnitKind kind() const noexcept = 0;
};

