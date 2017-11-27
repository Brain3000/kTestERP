#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <list>

enum class EmployerPosition {
    eUnknown,
    eProgrammer,
    eWriter,
    eTester,
    eAccountant
};

enum class Job {
    eProgramming,
    eProjecting,
    eTranslation,
    eTesting,
    ePlaningTest,
    ePaySallory,
    eReporting,
    eVacation,
    eCleaning,
};

class IEmployer
{
public:
    using Jobs = std::unordered_set<Job>;

public:    
    virtual ~IEmployer() {};
	virtual bool canJob(Job job) const noexcept = 0;
    virtual const std::string& name() const noexcept = 0;
    virtual EmployerPosition position() const noexcept = 0;
    virtual const Jobs& jobs() const noexcept = 0;
};

using IEmployerPtr = std::shared_ptr<IEmployer>;
struct EmployerEqual : std::unary_function<IEmployerPtr, bool>
{
    EmployerEqual(IEmployerPtr val) : m_val(val){}
    bool operator()(const IEmployerPtr& e1) const {
        return (e1->name() == m_val->name() && m_val->position() == e1->position());
    }
private:
    IEmployerPtr m_val;
};

class Employer : public IEmployer
{
public:
	virtual bool canJob(Job job) const noexcept;
    virtual const std::string& name() const noexcept;
    virtual EmployerPosition position() const noexcept;
    virtual const Jobs& jobs() const noexcept;

protected:
    Employer(const std::string& name, EmployerPosition position) noexcept;

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

class EmployerFactory
{
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

