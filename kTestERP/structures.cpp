#include "stdafx.h"
#include "structures.h"


bool EmployerBase::canDo(Job job)
{
    switch (job)
    {
    case Job::eVacation:
    case Job::eCleaning:
        return true;
    default:
        assert(false);
        return false;
    }
}



bool Departament::addEmployer(const EmployerBase& /*employer*/) {
    return true;
}

EmployersList&& Departament::getEmployers(EmployerPosition /*position*/) const {
    EmployersList employers;
    return std::move(employers);
}
