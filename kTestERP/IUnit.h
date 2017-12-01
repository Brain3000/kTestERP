#pragma once

#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <conio.h>

#include "Job.h"

using StringList = std::list<std::string>;

class IUnit {
public:
    virtual ~IUnit() {}
    virtual bool doJob(Job job, StringList& report) const = 0;
    virtual const std::string& name() const noexcept = 0;
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

template<typename C, typename K, typename I>
class UnitWChildrenImpl : public UnitImpl {
    using ChildPtr = std::shared_ptr<C>;
    using Children = K;
public:
    UnitWChildrenImpl(const std::string& name) :
        UnitImpl(name) {}
    virtual bool doJob(Job job, StringList& report) const {
        bool jobResult(false);
        auto beginIt = report.begin();
        for (auto it = m_children.begin(); it != m_children.end(); ++it) {
            if (child(it)->doJob(job, report) && !jobResult) {
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
    virtual ChildPtr child(I it) const noexcept = 0;

protected:
    Children m_children;
};

