#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <assert.h>

#include "IUnit.h"

enum class EmployerPosition {
    eUnknown,
    eProgrammer,
    eWriter,
    eTester,
    eAccountant
};

class IEmployer {
public:    
    virtual EmployerPosition position() const noexcept = 0;
    virtual const Jobs& jobs() const noexcept = 0;
};

class Departament;

class Employer : public UnitImpl<UnitKind::eEmployer>,
                 public IEmployer {
// IEmployer
public:
    virtual EmployerPosition position() const noexcept
        { return m_position; }
    virtual const Jobs& jobs() const noexcept
        { return m_jobs; }

// IUnit
public:
    virtual bool doJob(Job job);

public:
    Employer(const std::string& name, Departament* parent, EmployerPosition position) :
        UnitImpl(name), m_position(position), m_parent(parent){}

protected:
    Jobs m_jobs;

private:
    EmployerPosition m_position;
    Departament* m_parent;
};

using EmployerPtr = std::shared_ptr<Employer>;

template<EmployerPosition P, Job... jobs>
class EmployerImpl : public Employer {
public:
    EmployerImpl(const std::string& name, Departament* parent) :
        Employer(name, parent, P) {
            m_jobs = { { jobs... } };
            m_jobs.insert(Job::eCleaning);
            m_jobs.insert(Job::eVacation);
    }
};

using Programmer = EmployerImpl<EmployerPosition::eProgrammer, Job::eProgramming, Job::eProjecting>;
using Writer = EmployerImpl<EmployerPosition::eWriter, Job::eTranslation>;
using Tester = EmployerImpl<EmployerPosition::eWriter, Job::eTesting, Job::ePlaningTest>;
using Accountant = EmployerImpl<EmployerPosition::eWriter, Job::ePaySallory, Job::eReporting>;

//using EmployersMap = std::unordered_map<EmployerPosition, IEmployerPtr>;
//using EmployersMapPair = EmployersMap::value_type;

class EmployerFactory {
public:
    EmployerFactory(bool verbose) noexcept : m_verbose(verbose)
        {}
    EmployerPtr createEmployer(const std::string& name,
                               const std::string& positionAsText,
                               Departament* parent);
private:
    EmployerPosition textToPosition(const std::string& positionAsText);

private:
    bool m_verbose;
};

