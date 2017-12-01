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
};

const std::string job_to_str(Job job);

using Jobs = std::unordered_set<Job>;

