/**
\file
\brief Фабрика сотрудников
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include "Employer.h"

/// Создает сотрудника с указанной должностью и именем.
class EmployerFactory {
public:
    EmployerFactory(bool verbose) noexcept : m_verbose(verbose)
    {}
    /**
    \brief Создание сотрудника. 
    Создает сотрудника с указанной фамилией и указанной специальности,
    переданной в строковом виде. Если имя пустое или такой специальности нет,
    то возвращается пустой Ptr.
    \param[in] name фамилия сотрудника, должно быть непустое, иначе сотрудник не создастся.
    \param[in] positionAsText строковое представление должности сотрудника. 
    Если такой должности нет, то сотрудник не создастся.
    \return соданный сотрудник или пустой Ptr.
    */
    EmployerPtr createEmployer(const std::string& name,
        const std::string& positionAsText);

private:
    /// Флаг вывода отладочных сообщений при загрузке.
    bool m_verbose;
};
