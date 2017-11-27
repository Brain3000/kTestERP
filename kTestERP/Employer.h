#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <list>

enum class EmployerPosition {
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

class Employer
{
protected:
    using Jobs = std::unordered_set<Job>;

public:
    virtual ~Employer() {};
    bool canJob(Job job) const noexcept;

protected:
    Employer(const std::string& name, EmployerPosition position) noexcept;

private:
    const std::string m_name;
    EmployerPosition m_position;

protected:
    Jobs m_jobs;
};

using EmployerPtr = std::shared_ptr<Employer>;

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

using EmployersMap = std::unordered_map<EmployerPosition, EmployerPtr>;
using EmployersList = std::list<EmployerPtr>;

class EmployerFactory
{
public:
    EmployerPtr createEmployer(const std::string& name,
        EmployerPosition pos) noexcept;
};

