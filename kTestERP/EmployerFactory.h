#pragma once

#include "Employer.h"

class EmployerFactory {
public:
    EmployerFactory(bool verbose) noexcept : m_verbose(verbose)
    {}
    EmployerPtr createEmployer(const std::string& name,
        const std::string& positionAsText);

private:
    bool m_verbose;
};
