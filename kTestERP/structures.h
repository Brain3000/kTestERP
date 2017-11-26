#pragma once

#include <string>
#include <unordered_map>
#include <list>
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

struct EmployerBase {
    const std::string m_name;
    EmployerBase(std::string name) noexcept:
        m_name(name) {}
    virtual ~EmployerBase(){}
    bool canDo(Job job);

//protected:
//    bool isPrograming() const { return false; }
//    bool isProjecing() const { return false; }
//    bool isTranslating() const { return false; }
//    bool isTesting() const { return false; }
//    bool isPlainingTest() const { return false; }
//    bool isPaySallory() const { return false; }
//    bool isReporting() const { return false; }
};



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

using EmployersMap = std::unordered_map<EmployerPosition, EmployerBase>;
using EmployersList = std::list<EmployerBase>;

class Departament {
public:
    Departament(std::string name) noexcept :
        m_name(name) {}
    bool addEmployer(const EmployerBase& employer);
    EmployersList&& getEmployers(EmployerPosition position) const;

private:
    const std::string m_name;
    EmployersMap m_employers;
};
