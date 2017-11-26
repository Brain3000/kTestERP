#include "stdafx.h"
#include "structures.h"


//bool EmployerBase::canDo(Job job)
//{
//    switch (job)
//    {
//    case Job::eVacation:
//    case Job::eCleaning:
//        return true;
//    default:
//        assert(false);
//        return false;
//    }
//}

IEmployerPtr EmployerFactory::createEmployer(const std::string& name,
                                           EmployerPosition pos) noexcept {
    switch (pos)
    {
    case EmployerPosition::eProgrammer:
        return std::make_shared<Programmer>(name);
    case EmployerPosition::eWriter:
        return std::make_shared<Writer>(name);
    case EmployerPosition::eTester:
        return std::make_shared<Tester>(name);
    case EmployerPosition::eAccountant:
        return std::make_shared<Accountant>(name);
    default:
        assert(false);
        break;
    }
}


bool Departament::addEmployer(IEmployerPtr /*employer*/) {
    return true;
}

EmployersList&& Departament::getEmployers(EmployerPosition /*position*/) const {
    EmployersList employers;
    return std::move(employers);
}
