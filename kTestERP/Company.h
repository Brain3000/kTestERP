/**
\file
\brief Реализация класса Компания
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include <unordered_map>

#include "Departament.h"

using DepartamentPtr = std::shared_ptr<Departament>;
using Departaments = std::unordered_map<std::string, DepartamentPtr>;

/// Реализация класса для компании
class Company : public UnitWChildrenImpl<Departament, Departaments, UnitKind::eCompany>
{
public:
    /// Создает компанию с дефолтным именем.
    Company() : UnitWChildrenImpl("Наша фирма"){}
    /**
    \brief Создает и/или возвращает отдел с указанным именем.
    
    Возвращает отдел с именем, которое передали, если такого отдела
    нет, то создает его пустым (без сотрудников) и возвращает.
    */
    DepartamentPtr getOrCreateDept(const std::string& deptName);

    /// Возвращает по итератору отдел.
    DepartamentPtr child(Departaments::const_iterator it) const noexcept;
};

