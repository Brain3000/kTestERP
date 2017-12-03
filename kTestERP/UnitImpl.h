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
public:
    using ChildPtr = std::shared_ptr<U>;
    using Children = C;
    using Iterator = typename C::const_iterator;

    UnitWChildrenImpl(const std::string& name) :
        UnitImpl(name, K) {}
    virtual bool doJob(Job job, StringList& report) const;
    const Children& getChildren() const noexcept {
        return m_children;
    }
    virtual ChildPtr child(Iterator it) const noexcept = 0;
    ChildPtr childByName(const std::string& name) const noexcept;

protected:
    Children m_children;
};


template<typename U, typename C, UnitKind K>
bool UnitWChildrenImpl<U, C, K>::doJob(Job job, StringList& report) const {
    std::string msg = kind_to_str(m_kind);
    msg.append(" '");
    msg.append(m_name);
    msg.append("' работу ");
    if (m_children.empty()) {
        msg.append("выполнить не может, поскольку отсутствуют подчиненные структурные единицы");
        report.push_back(msg);
        return false;
    }

    bool jobResult(false);
    for (auto it = m_children.begin(); it != m_children.end(); ++it) {
        if (child(it)->doJob(job, report) && !jobResult) {
            jobResult = true;
        }
    }
    msg.append(jobResult ? "выполнил(а)" : "выполнить не может");
    report.push_back(msg);
    return jobResult;
}

template<typename U, typename C, UnitKind K>
typename UnitWChildrenImpl<U, C, K>::ChildPtr
UnitWChildrenImpl<U, C, K>::childByName(const std::string& name) const noexcept {
    ChildPtr res;
    for (auto it = m_children.cbegin(); it != m_children.end(); ++it) {
        ChildPtr tmp = child(it);
        if (tmp->name() == name) {
            std::swap(res, tmp);
            break;
        }
    }
    return res;
}
