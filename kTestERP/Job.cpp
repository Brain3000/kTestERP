#include "stdafx.h"

#include <unordered_map>

#include "Job.h"

const std::string job_to_str(Job job) {
    using JobMap = std::unordered_map<Job, std::string>;
    static const JobMap m_jobMap{
        { Job::eProgramming, "программировать" },
        { Job::eProjecting,  "проектировать" },
        { Job::eTranslation, "переводить" },
        { Job::eTesting,     "тестировать" },
        { Job::ePlaningTest, "планировать тестирование" },
        { Job::ePaySallory,  "начислять зарплату" },
        { Job::eReporting,   "составлять отчет" },
        { Job::eVacation,    "идти в отпуск" },
        { Job::eCleaning,    "убирать рабочее место" },
    };
    return m_jobMap.at(job);
}

