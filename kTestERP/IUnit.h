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

enum class UnitKind
{
    eCompany,
    eDepartament,
    eEmployer,
};


class IUnit {
public:
    virtual ~IUnit() {}
    virtual bool doJob(Job job) = 0;
    virtual const std::string& name() const noexcept = 0;
    virtual UnitKind kind() const noexcept = 0;
    virtual void printReport() = 0;
    virtual void clearReport() = 0;
};

using StringList = std::list<std::string>;

template<UnitKind K>
class UnitImpl : public IUnit {
    static const size_t kRepRecordMaxCount = 20;
public:
    UnitImpl(const std::string& name) : m_name(name)
        {}

    virtual const std::string& name() const noexcept {
        return m_name;
    }

    virtual UnitKind kind() const noexcept {
        return K;
    }

    virtual void printReport() {
        assert(!m_report.empty());
        if (m_report.empty()) {
            std::cout << m_name << " : действий не выполн€лось\n";
        }
        size_t cnt(0);
        for (const auto rep : m_report) {
            if (cnt++ < kRepRecordMaxCount) {
                std::cout << rep << std::endl;
            }
            else {
                std::cout << "¬ывести следующие записи? "
                    "(люба€ кнопка дл€ продолжени€, 'n' дл€ выхода)\n";
                if (_getch() == 'n') {
                    break;
                }
                cnt = 0;
            }
        }
    }
    virtual void clearReport() {
        m_report.clear();
    }

protected:
    const std::string m_name;
    StringList m_report;
};

template<UnitKind K, typename C>
class UnitWChildrenImpl : public UnitImpl<K> {
    using ChildPtr = std::shared_ptr<C>;
    using Children = std::list<ChildPtr>;
public:
    UnitWChildrenImpl(const std::string& name) :
        UnitImpl(name) {}
    virtual bool doJob(Job job) {
        bool res(false);
        clearReport();
        for (auto c : m_children) {
            if (c->doJob(job) && !res) {
                res = true;
            }
        }
        return res;
    }
    virtual void clearReport() noexcept {
        for (auto c : m_children) {
            c->clearReport();
        }
    }

protected:
    Children m_children;
    StringList m_report;
};

//template<UnitKind K, typename P>
//class UnitWParentImpl : public UnitImpl<K> {
//public:
//    UnitWParentImpl(const std::string& name, P* parent) :
//        UnitImpl(name), m_parent(parent) {}
//    virtual void addRepRecord(const std::string& record) {
//        m_report.push_back(record);
//        assert(m_parent);
//        if (m_parent)
//            m_parent->addChildReport(m_name + ": " + record);
//    }
//protected:
//    P* m_parent;
//};
