#include "stdafx.h"

#include <assert.h>

#include "Employer.h"


Employer::Employer(const std::string& name,
                   EmployerPosition position) noexcept :
    m_name(name), m_position(position) {
    m_jobs = { Job::eVacation, Job::eCleaning };
}

bool Employer::canJob(Job job) const noexcept {
    return (m_jobs.find(job) != m_jobs.end());
}

EmployerPtr EmployerFactory::createEmployer(const std::string& name,
    EmployerPosition pos) noexcept {
    switch (pos)
    {
    case EmployerPosition::eProgrammer:
        return std::shared_ptr<Employer>(new Programmer(name));
    case EmployerPosition::eWriter:
        return std::shared_ptr<Employer>(new Writer(name));
    case EmployerPosition::eTester:
        return std::shared_ptr<Employer>(new Tester(name));
    case EmployerPosition::eAccountant:
        return std::shared_ptr<Employer>(new Accountant(name));
    default:
        assert(false);
        break;
    }
    return nullptr;
}

