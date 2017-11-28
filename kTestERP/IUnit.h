#pragma once

#include <memory>
#include <list>
#include <string>
#include <unordered_set>


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

class IUnit;
using IUnitPtr = std::shared_ptr<IUnit>;
using UnitList = std::list<IUnitPtr>;

const UnitList kEmptyUnitList;

class IUnit {
public:
    virtual ~IUnit() {}
    virtual bool canDo(Job job) const noexcept = 0;
    virtual const std::string& name() const noexcept = 0;
    virtual const UnitList& getChild() const noexcept = 0;
    virtual UnitKind kind() const noexcept = 0;
};

template<UnitKind K>
class UnitImpl : public IUnit {
public:
    explicit UnitImpl(const std::string& name) : m_name(name)
        {}
    virtual UnitKind kind() const noexcept {
        return K;
    }
    const UnitList& getChild() const noexcept {
        return m_childs;
    }
    virtual bool canDo(Job job) const noexcept {
        const auto it =
            std::find_if(m_childs.begin(), m_childs.end(),
                [job](const auto c) { return c->canDo(job); });
        return (it != m_childs.end());
    }

protected:
    UnitList m_childs;
    const std::string m_name;
};
