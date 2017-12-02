#pragma once

#include <unordered_set>

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

    eFirst = eProgramming,
    eLast = eCleaning,
};

const std::string job_to_str(Job job);
Job str_to_job(const std::string& jobName);

using Jobs = std::unordered_set<Job>;

