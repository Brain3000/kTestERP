#include "stdafx.h"

#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <assert.h>

#include "Job.h"
#include "EnumImpl.h"

using JobStrMap = std::unordered_map<Job, std::string>;

const JobStrMap& get_job_str_map() {
    static const JobStrMap s_jobStrMap = {
        { Job::eProgramming, "Программировать" },
        { Job::eProjecting,  "Проектировать" },
        { Job::eTranslation, "Переводить" },
        { Job::eTesting,     "Тестировать" },
        { Job::ePlaningTest, "Планировать тестирование" },
        { Job::ePaySallory,  "Начислять зарплату" },
        { Job::eReporting,   "Составлять отчет" },
        { Job::eVacation,    "Идти в отпуск" },
        { Job::eCleaning,    "Убирать рабочее место" },
    };
#ifdef _DEBUG
    for (auto e : EnumImpl<Job>()) {
        assert(s_jobStrMap.find(e) != s_jobStrMap.end());
    }
#endif // _DEBUG

    return s_jobStrMap;
}

const std::string job_to_str(Job job) {
    return get_job_str_map().at(job);
}

Job str_to_job(const std::string& jobName) {
    using StrJobMap = std::unordered_map<std::string, Job>;
    static StrJobMap s_strJobMap;

    const JobStrMap& jobStrMap = get_job_str_map();

    if (s_strJobMap.empty()) {
        std::transform(jobStrMap.begin(),
            jobStrMap.end(),
            std::inserter(s_strJobMap, s_strJobMap.begin()),
            [](auto pair) { return std::make_pair(pair.second, pair.first);  });
    }
    return s_strJobMap.at(jobName);
}
