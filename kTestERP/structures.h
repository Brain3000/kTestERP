#pragma once

#include <string>
#include <unordered_set>
#include <assert.h>

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



//template<typename T, typename T::Val>
struct EmployerBase {
    const std::string m_name;
    EmployerBase(std::string name) noexcept:
        m_name(name) {}
    bool canDo(Job job);

protected:
    bool isPrograming() const { return false; }
    bool isProjecing() const { return false; }
    bool isTranslating() const { return false; }
    bool isTesting() const { return false; }
    bool isPlainingTest() const { return false; }
    bool isPaySallory() const { return false; }
    bool isReporting() const { return false; }
};

bool EmployerBase::canDo(Job job)
{
    switch (job)
    {
    case Job::eProgramming:
        return isPrograming();
    case Job::eVacation:
    case Job::eCleaning:
        return true;
    default:
        assert(false);
        return false;
    }
}


//template<typename T>
//struct Employer<T::eProgramming>
//{
//protected:
//    bool isPrograming() const { return true; }
//};
//
//template<typename T>
//struct Employer<T::eProjecing>
//{
//protected:
//    bool isProjecing() const { return true; }
//};
//
//template<typename T>
//struct Employer<T::eTranslating>
//{
//protected:
//    bool isTranslating() const { return true; }
//};

using Employers = std::unordered_set<EmployerBase>;

class Departament {
public:
    bool addEmployer(const EmployerBase& employer);
    Employers&& getEmployers(EmployerPosition position) const;

private:
    const std::string m_name;
    Employers m_employers;
};
