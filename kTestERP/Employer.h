#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <list>

#include "IUnit.h"

enum class EmployerPosition {
    eUnknown,
    eProgrammer,
    eWriter,
    eTester,
    eAccountant
};

class IEmployer : public IUnit {
public:    
    virtual EmployerPosition position() const noexcept = 0;
    virtual const Jobs& jobs() const noexcept = 0;
};

using IEmployerPtr = std::shared_ptr<IEmployer>;

//template<EmployerPosition P, Job... jobs>
class Employer : public IEmployer {
// IEmployer
public:
    virtual EmployerPosition position() const noexcept
        { return m_position; }
    virtual const Jobs& jobs() const noexcept
        { return m_jobs; }

// IUnit
public:
    virtual bool canDo(Job job) const noexcept
        { return (m_jobs.find(job) != m_jobs.end()); }
    virtual const std::string& name() const noexcept
        { return m_name; }
    virtual const UnitList& getChild() const noexcept
        { return kEmptyUnitList; }
    virtual UnitKind kind() const noexcept
        { return UnitKind::eEmployer; }

public:
    Employer(const std::string& name, EmployerPosition position) :
        m_name(name), m_position(position) {}
    //{
    //    Jobs j = { { jobs... } };
    //    m_jobs.insert(j.begin(), j.end());
    //}

protected:
    Jobs m_jobs;

private:
    const std::string m_name;
    EmployerPosition m_position;
};


template<EmployerPosition P, Job... jobs>
class EmployerImpl : public Employer {
public:
    EmployerImpl(const std::string& name) :
    Employer(name, P) {
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
    IEmployerPtr createEmployer(const std::string& name,
                                const std::string& positionAsText);
private:
    EmployerPosition textToPosition(const std::string& positionAsText);

private:
    bool m_verbose;
};

