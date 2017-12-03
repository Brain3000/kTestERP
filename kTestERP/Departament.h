/**
\file
\brief Реализация класса Отдела
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include <set>

#include "Employer.h"

/**
\brief Функтор для сравнения сотрудников в рамках отдого отдела.
Сотрудники сравниваются по имени и должности. В приоритете имя.
*/
struct EmployerLess : std::binary_function<EmployerPtr, EmployerPtr, bool> {
    bool operator()(EmployerPtr e1, EmployerPtr e2) const {
        int cmpRes = e1->name().compare(e2->name());
        if (!cmpRes)
            return e1->position() < e2->position();
        return (cmpRes < 0);
    }
};
using Employers = std::set<EmployerPtr, EmployerLess>;

// Реализация класс Отдела.
class Departament : public UnitWChildrenImpl<Employer, Employers, UnitKind::eDepartament> {
public:
    /// Создается отдел с указанным именем.
    Departament(std::string name) :
        UnitWChildrenImpl(name){}
    /**
    \brief Добавить сотрудника в отдел.
    Пытается добавить сотрудника в отдел. Если сотрудник с таким именем и должностью уже есть в отделе
    то новый сотрудник не будет добавлен.
    \param[in] employer сотрудник, которого необходимо добавить.
    \return в случае успешного добавления возвращает true.
    */
    bool addEmployer(EmployerPtr employer);
    /**
    \brief Возвращает по итератору контейнера сотрудника.
    
    \details Это надо потому, что контейнеры разные и универсальный метод *it может
    не прокатить. Например если *it - это std::pair
    */
    virtual EmployerPtr child(Employers::const_iterator it) const noexcept;

    /// Возвращает описание отдела. В данной реализации это полный эквивалент имени.
    std::string description() const;
};
