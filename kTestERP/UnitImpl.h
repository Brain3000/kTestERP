/**
\file
\brief Базовая реализация для всех структурных единиц
и для структурных единиц с подчиненными объектами.
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include <memory>
#include <algorithm>

#include "IUnit.h"

/// Метод возвращает строкое представление по типу юнита.
const std::string& kind_to_str(UnitKind kind);

/**
    \braef Базовая реализация всех юнитов.
    Тут реализованы тривиальные методы и общие данные.
    Метода, возвращающего m_report нет умышленно, поскольку 
    разное поведение у юнитов, которые имеют подчиненные элементы
    и не имеют их в случае, если работы не выполнялись вообще.
    (Работы могут не выполнятся, поскольку никто не может сделать
    этот тип работ или нет подчиненных элементов).
*/
class UnitImpl : public IUnit {
public:
    UnitImpl(const std::string& name, UnitKind kind) : m_name(name), m_kind(kind)
    {}
    /// Возвращает имя структурной единицы.
    virtual const std::string& name() const noexcept {
        return m_name;
    }

    /// Возвращает тип структурной единицы.
    virtual UnitKind kind() const noexcept {
        return m_kind;
    }

protected:
    std::string m_name;
    UnitKind m_kind;
    std::string m_report;
};

/**
    \brief Базовая реализация для структурных подразделений, которые 
    могут содержать в себе другие структурные подразделения.
    U - тип подчиненного структурного подразделения
    C - тип контейнера, в котором будут хранится подчиненные элементы
    K - тип данного структурного подразделения
*/
template<typename U, typename C, UnitKind K>
class UnitWChildrenImpl : public UnitImpl {
public:
    using ChildPtr = std::shared_ptr<U>;
    using Children = C;
    using Iterator = typename C::const_iterator;

    /// Конструктор. Передается имя, тип берется из шаблона.
    UnitWChildrenImpl(const std::string& name);

    /**
    \brief Конечная реализация метода "ВыполнитьРаботу" для
    структурного подразделения с подчиненными
    \param[in] job - тип работы
    \param[out] report - отчет о выполнении работы
    \return в случае, если сотрудник может выполнить работу данного
    типа - возвращает true
    */
    virtual bool doJob(Job job, StringList& report);

    /// Получить контейнер с подчиненными элементами
    const Children& getChildren() const noexcept {
        return m_children;
    }

    /// Получить подчиненный элемент по итератору
    /// *it не для всех контейнеров прокатывает.
    virtual ChildPtr child(Iterator it) const noexcept = 0;

    /// Получить подчиненного по имени.
    /// \return в случае успеха возвращает подчиненый элемент.
    /// Иначе - пустой указатель.
    ChildPtr childByName(const std::string& name) const noexcept;

    /// Возвращает отчет о работе только данного юнита.
    /// Без информации о подчиненных.
    virtual const std::string& report() const noexcept;

protected:
    Children m_children;

private:
    std::string m_emptyReport; ///< Пустой отчет - текст, который возвращается, если никакие работы не делались.
};

template<typename U, typename C, UnitKind K>
UnitWChildrenImpl<U, C, K>::UnitWChildrenImpl(const std::string& name) :
    UnitImpl(name, K),
    m_emptyReport("Структурное подразделение " + kind_to_str(K) + " '" + name + "' работ невыполняло.") {
}



template<typename U, typename C, UnitKind K>
bool UnitWChildrenImpl<U, C, K>::doJob(Job job, StringList& report) {
    std::string msg("Работу '");
    msg.append(job_to_str(job));
    msg.append("' структурное подразделение ");
    msg.append(kind_to_str(kind()));
    msg.append(" '");
    msg.append(m_name);
    msg.append("'");
    if (m_children.empty()) {
        msg.append("' выполнить не может, поскольку отсутствуют подчиненные структурные единицы.");
        report.push_back(msg);
        return false;
    }

    StringList internalReport;
    bool jobResult(false);
    for (auto it = m_children.begin(); it != m_children.end(); ++it) {
        if (child(it)->doJob(job, internalReport) && !jobResult) {
            jobResult = true;
        }
    }
    msg.append(jobResult ? "' выполнил(а)." : "' выполнить не может.");
    report.push_back(msg);
    std::swap(msg, m_report);
    std::transform(internalReport.begin(), internalReport.end(), std::back_inserter(report),
        [](std::string s) { s.insert(s.begin(), 4, ' '); return s; });
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

template<typename U, typename C, UnitKind K>
const std::string& UnitWChildrenImpl<U, C, K>::report() const noexcept{
    return (m_report.empty() ? m_emptyReport : m_report);
}
