#pragma once

#include <memory>
#include <list>
#include <string>
#include <unordered_set>
#include <algorithm>

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

enum class UnitKind
{
    eCompany,
    eDepartament,
    eEmployer,
};

//class IUnit;
//using IUnitPtr = std::shared_ptr<IUnit>;
using StringList = std::list<std::string>;

class IUnit {
public:
    virtual ~IUnit() {}
    virtual bool doJob(Job job) const noexcept = 0;
    virtual const std::string& name() const noexcept = 0;
    virtual UnitKind kind() const noexcept = 0;
    virtual IUnit* parent() const noexcept = 0;
    virtual void clearReport() noexcept = 0;
    virtual void addRepRecord(const std::string& record) = 0;
};

template<UnitKind K>
class UnitImpl : public IUnit {
public:
    UnitImpl(const std::string& name, IUnit* parent = nullptr) : m_name(name)
        {}
    virtual UnitKind kind() const noexcept {
        return K;
    }
    virtual const std::string& name() const noexcept
        { return m_name; }

    virtual IUnit* parent() const noexcep
        { return m_parent; }
protected:
    const std::string m_name;
    IUnit* m_parent;
};

template<UnitKind K, typename C>
class UnitWChildrenImpl : public UnitImpl<K> {
    using ChildPtr = std::shared_ptr<C>;
    using Children = std::list<ChildPtr>;
public:
    UnitWChildrenImpl(const std::string& name, IUnit* parent = nullptr) :
        UnitImpl(name, parent) {}
    virtual bool doJob(Job job) const noexcept {
        auto it =
            std::find_if(m_children.begin(), m_children.end(),
                [job](auto c) { return c->doJob(job); });
        return (it != m_children.end());
    }
    virtual void clearReport() noexcept {
        for (auto c : m_children) {
            c->reportClear();
        }
    }
    virtual void addRepRecord(const std::string& record) {
        m_report.push_back(record);
        for (auto c : m_children) {
            c->addRepRecord(m_name + ": " + record);
        }
    }
protected:
    Children m_children;
    StringList m_report;
};