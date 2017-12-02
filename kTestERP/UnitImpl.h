#pragma once

#include <memory>

#include "IUnit.h"

const std::string& kind_to_str(UnitKind kind);

class UnitImpl : public IUnit {
public:
    UnitImpl(const std::string& name, UnitKind kind) : m_name(name), m_kind(kind)
    {}
    virtual const std::string& name() const noexcept {
        return m_name;
    }
    virtual UnitKind kind() const noexcept {
        return m_kind;
    }

protected:
    std::string m_name;
    UnitKind m_kind;
};

template<typename U, typename C, UnitKind K>
class UnitWChildrenImpl : public UnitImpl {
    using ChildPtr = std::shared_ptr<U>;
    using Children = C;
    using Iterator = typename C::const_iterator;
public:
    UnitWChildrenImpl(const std::string& name) :
        UnitImpl(name, K) {}
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
    virtual ChildPtr child(Iterator it) const noexcept = 0;

protected:
    Children m_children;
};

