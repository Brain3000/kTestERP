#include "stdafx.h"

#include <unordered_map>

#include "Job.h"

const std::string job_to_str(Job job) {
    using JobMap = std::unordered_map<Job, std::string>;
    static const JobMap m_jobMap{
        { Job::eProgramming, "Программировать" },
        { Job::eProjecting,  "Проектировать" },
        { Job::eTranslation, "Переводить" },
        { Job::eTesting,     "Тестировать" },
        { Job::ePlaningTest, "Планировать тестирование" },
        { Job::ePaySallory,  "Пачислять зарплату" },
        { Job::eReporting,   "Составлять отчет" },
        { Job::eVacation,    "Идти в отпуск" },
        { Job::eCleaning,    "Убирать рабочее место" },
    };
    return m_jobMap.at(job);
}

