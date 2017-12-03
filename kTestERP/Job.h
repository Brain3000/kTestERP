/**
\file
\brief Перечисление видов работы и обслуживающие его сервисные функции
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include <unordered_set>

/// Перечисление видов работ, которые могут выполнять структурные единицы фирмы
enum class Job {
    eProgramming,   ///< Программировать
    eProjecting,    ///< Проектировать    
    eTranslation,   ///< Переводить тексты
    eTesting,       ///< Тестировать
    ePlaningTest,   ///< Составлять тестовые планы
    ePaySallory,    ///< Начислять зарплату
    eReporting,     ///< Составлять квартальный отчет
    eVacation,      ///< Уйти в отпуск
    eCleaning,      ///< Убрать рабочее место

    eFirst = eProgramming,  ///< Первый и последний элемент для итерирования
    eLast = eCleaning,
};

/// Получить текстовое представление работы
const std::string job_to_str(Job job);

/// Получить значение перечисления по текстовому представлению
/// Если по тексту получить значение перечисления нельзя, то
/// Кидается std::out_of_range
Job str_to_job(const std::string& jobName);

/// Список работы (порядок не имеет значения)
using Jobs = std::unordered_set<Job>;

