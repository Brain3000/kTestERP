/**
\file
\brief Реализация сущности Сотрудник с сопуствующими обвязками.
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <list>
#include <assert.h>

#include "UnitImpl.h"

/// Виды должностей сотрудников.
enum class EmployerPosition {
    eProgrammer,    ///< Разработчик
    eWriter,        ///< Технический писатель
    eTester,        ///< Специалист тестирования
    eAccountant,    ///< Бухгалтер

    eFirst = eProgrammer,   ///< Первый и последний элементы перечисления для итерирования
    eLast = eAccountant,
};

/// Возвращает по должности её строковое представление.
const std::string& pos_to_str(EmployerPosition pos);

/// По строковому представлению определяет перечисление для должности.
/// В случае, если по строковому представлению перечисление не определили,
/// кидается std::out_of_range
EmployerPosition str_to_pos(const std::string& posAsStr);

/// Реализация класса для Сотрудника
class Employer : public UnitImpl {

public:
    /// Возвращает должность
    virtual EmployerPosition position() const noexcept
        { return m_position; }
    /// Возвращает список работ, которые может выполнять
    /// сотрудник (на данной должности)
    virtual const Jobs& jobs() const noexcept
        { return m_jobs; }

// IUnit
public:
    /**
        \brief Выполнить работу
        \param[in] job - тип работы
        \param[out] report - отчет о выполнении работы
        \return в случае, если сотрудник может выполнить работу данного
        типа - возвращает true
    */    
    virtual bool doJob(Job job, StringList& report);

    /// Возвращает отчет о работе только данного сотрудника
    /// или отчет об отсутсвии работы
    virtual const std::string& report() const noexcept;

public:
    /**
    \brief Конструктор. Передается имя и должность.
    \param[in] фамилия сотрудника
    \param[in] занимаемая должность
    */
    Employer(const std::string& name, EmployerPosition position);

protected:
    Jobs m_jobs; /// Список работ, которые сотрудник может сделать

private:
    EmployerPosition m_position; /// Должность
    std::string m_emptyReport;   /// Текст отчета, который возвращается,
                                 /// если никакие работы не производились.
};

using EmployerPtr = std::shared_ptr<Employer>;

/**
    \brief Шаблонный класс для облегчения реализации сотрудников
    на разных должностях и разным списком выполняемых работ.

    \details В параметрах шаблона передается должность и список
    работ, которе он может выполнять.
*/
template<EmployerPosition P, Job... jobs>
class EmployerImpl : public Employer {
public:
    EmployerImpl(const std::string& name) :
        Employer(name, P) {
            m_jobs = { { jobs... } };
            /// Во все реализации добавляются общие работы "Отпуск" и "Уборка рабочего места".
            m_jobs.insert(Job::eCleaning);
            m_jobs.insert(Job::eVacation);
    }
};

/// Программист (может программировать и проектировать).
using Programmer = EmployerImpl<EmployerPosition::eProgrammer, Job::eProgramming, Job::eProjecting>;
/// Техпис (может переводить).
using Writer = EmployerImpl<EmployerPosition::eWriter, Job::eTranslation>;
/// Тестировщик (может тестировать и составлять план тестирования)
using Tester = EmployerImpl<EmployerPosition::eTester, Job::eTesting, Job::ePlaningTest>;
/// Бухгалтер (может начислять зарплату и делать отчет)
using Accountant = EmployerImpl<EmployerPosition::eAccountant, Job::ePaySallory, Job::eReporting>;


