#include "stdafx.h"

#include "Departament.h"



bool Departament::addEmployer(EmployerPtr /*employer*/) {
    return true;
}

EmployersList&& Departament::getEmployers(EmployerPosition /*position*/) const {
    EmployersList employers;
    return std::move(employers);
}
