#pragma once

#include <memory>
#include <list>
#include <string>


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
    virtual const UnitList& getChild() const noexcept {
        return m_childs;
    }
protected:
    UnitList m_childs;
    const std::string m_name;
};

template<>
class UnitImpl<UnitKind::eEmployer> : public IUnit
{
public:
    virtual UnitKind kind() const noexcept {
        return UnitKind::eEmployer;
    }
    virtual const UnitList& getChild() const noexcept {
        return kEmptyUnitList;
    }

};