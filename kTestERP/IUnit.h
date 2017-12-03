/**
    \file
    \brief Самые базовые конструкции задачи: перечисление типов юнитов и общий интерфейс юнита.
    \author Leontyev George
    \version 1.0
    \date Ноябрь 2017
*/
#pragma once


#include <list>
#include <string>
#include <iostream>
#include <assert.h>

#include "Job.h"

/// Перечисление типов используемых в приложении юнитов.
enum class UnitKind {
    eCompany,           ///< Компания
    eDepartament,       ///< Отдел
    eEmployer,          ///< Сотрудник

    eFirst = eCompany,  ///< Первый и последний элемент для итерирования по перечислению.
    eLast = eEmployer,
};

using StringList = std::list<std::string>;

/**
    \bref Интерфейс для всех юнитов: фирмы, отдела и сотрудника
    содержит базовый набор общих функций.
    
    Все юниты имеют имя, тип (фирма, отдел, сотрудник),
    могут получать приказ на выполнение работ, а также отдавать отчет.
*/
class IUnit {
public:
    virtual ~IUnit() {}
    /**
    \bref Получение и обработка приказа на выполнение работы.
    \param[in] job тип работ.
    \param[out] report отчет, возвращаемый вызываемой стороне,
    необходим, чтобы подробный отчет по отделу/фирме получался
    без необходимости повторного обхода структуры фирмы и без
    необходимости после каждого doJob вызывать report
    \return в случае, если юнит может выполнить работу типа job
    возвраз
    */
    virtual bool doJob(Job job, StringList& report) = 0;

    /// Возвращает имя юнита
    virtual const std::string& name() const noexcept = 0;
    /// Возвращает тип юнита
    virtual UnitKind kind() const noexcept = 0;
    /// Возвращает текстовый отчет по данному юниту без
    /// информации по подчиненным юнитам
    virtual const std::string& report() const noexcept = 0;
};

