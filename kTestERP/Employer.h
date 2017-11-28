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
struct EmployerEqual : std::unary_function<IEmployerPtr, bool> {
    EmployerEqual(IEmployerPtr val) : m_val(val){}
    bool operator()(const IEmployerPtr& e1) const {
        return (e1->name() == m_val->name() && m_val->position() == e1->position());
    }
private:
    IEmployerPtr m_val;
};

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

protected:
    Employer(const std::string& name, EmployerPosition position) noexcept :
        m_name(name), m_position(position) {}

private:
    const std::string m_name;
    EmployerPosition m_position;

protected:
    Jobs m_jobs;
};


template<EmployerPosition P, Job... jobs>
class EmployerImpl : public Employer {
public:
    EmployerImpl(const std::string& name) noexcept :
    Employer(name, P) {
        Jobs j = { { jobs... } };
        m_jobs.insert(j.begin(), j.end());
    }
};

using Programmer = EmployerImpl<EmployerPosition::eProgrammer, Job::eProgramming, Job::eProjecting>;
using Writer = EmployerImpl<EmployerPosition::eWriter, Job::eTranslation>;
using Tester = EmployerImpl<EmployerPosition::eWriter, Job::eTesting, Job::ePlaningTest>;
using Accountant = EmployerImpl<EmployerPosition::eWriter, Job::ePaySallory, Job::eReporting>;

using EmployersMap = std::unordered_map<EmployerPosition, IEmployerPtr>;
using EmployersMapPair = EmployersMap::value_type;
using EmployersList = std::list<IEmployerPtr>;

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

