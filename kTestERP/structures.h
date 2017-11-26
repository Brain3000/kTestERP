#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <assert.h>

enum class EmployerPosition {
    eProgrammer,
    eWriter,
    eTester,
    eAccountant
};

enum Job {
    eProgramming    = 1,
    eProjecting     = 2,
    eTranslation    = 4,
    eTesting        = 8,
    ePlaningTest    = 16,
    ePaySallory     = 32,
    eReporting      = 64,
    eVacation       = 128,
    eCleaning       = 256,
};

struct IEmployer
{
    virtual bool canDo(Job job) = 0;
    virtual ~IEmployer(){}
};

using IEmployerPtr = std::shared_ptr<IEmployer>;

template<EmployerPosition P, Job... jobs>
struct EmployerBase : public IEmployer {
    const std::string m_name;
    const EmployerPosition m_pos = P;
    EmployerBase(const std::string& name) noexcept :
        m_name(name) {
        std::array<Job, sizeof...(jobs)> j = { {jobs...} };
        m_jobs = std::accumulate(j.begin(), j.end(), 0);
        m_jobs |= Job::eVacation;
        m_jobs |= Job::eCleaning;
    }
    virtual bool canDo(Job job) {
        return (job & m_jobs);
    }

private:
    uint32_t m_jobs;
};

using Programmer = EmployerBase<EmployerPosition::eProgrammer, Job::eProgramming, Job::eProjecting>;
using Writer = EmployerBase<EmployerPosition::eWriter, Job::eTranslation>;
using Tester = EmployerBase<EmployerPosition::eWriter, Job::eTesting, Job::ePlaningTest>;
using Accountant = EmployerBase<EmployerPosition::eWriter, Job::ePaySallory, Job::eReporting>;


class EmployerFactory
{
    IEmployerPtr createEmployer(const std::string& name,
                                EmployerPosition pos) noexcept;
};

using EmployersMap = std::unordered_map<EmployerPosition, IEmployerPtr>;
using EmployersList = std::list<IEmployerPtr>;

class Departament {
public:
    Departament(std::string name) noexcept :
        m_name(name) {}
    bool addEmployer(IEmployerPtr employer);
    EmployersList&& getEmployers(EmployerPosition position) const;
    const std::string& name() const { return m_name;  }
private:
    const std::string m_name;
    EmployersMap m_employers;
};

struct DepartamentHash
{
    size_t operator()(const Departament& dep) const
    {
        return dep.name().length();
    }
};

using Departaments = std::unordered_set<Departament, DepartamentHash>;
