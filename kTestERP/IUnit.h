#pragma once

#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <conio.h>

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

using Jobs = std::unordered_set<Job>;

//enum class UnitKind
//{
//    eCompany,
//    eDepartament,
//    eEmployer,
//};

using StringList = std::list<std::string>;

class IUnit {
public:
    virtual ~IUnit() {}
    virtual bool doJob(Job job, StringList& report) const = 0;
    virtual const std::string& name() const noexcept = 0;
    //virtual UnitKind kind() const noexcept = 0;
};

class UnitImpl : public IUnit {
public:
    UnitImpl(const std::string& name) : m_name(name)
        {}
    const std::string& name() const noexcept {
        return m_name;
    }
protected:
    const std::string m_name;
};

template<typename C>
class UnitWChildrenImpl : public UnitImpl {
    using ChildPtr = std::shared_ptr<C>;
    using Children = std::list<ChildPtr>;
public:
    UnitWChildrenImpl(const std::string& name) :
        UnitImpl(name) {}
    virtual bool doJob(Job job, StringList& report) const {
        bool jobResult(false);
        auto beginIt = report.begin();
        for (auto c : m_children) {
            if (c->doJob(job, report) && !jobResult) {
                jobResult = true;
            }
        }
        std::string msg = m_name;
        msg.append(" работу ");
        msg.append(jobResult ? "выполнил(а)" : "выполнить не может");
        report.emplace(beginIt, msg);
        return jobResult;
    }

protected:
    Children m_children;
};

