#include "stdafx.h"

#include <unordered_map>

#include "Job.h"

const std::string job_to_str(Job job) {
    using JobMap = std::unordered_map<Job, std::string>;
    static const JobMap m_jobMap{
        { Job::eProgramming, "���������������" },
        { Job::eProjecting,  "�������������" },
        { Job::eTranslation, "����������" },
        { Job::eTesting,     "�����������" },
        { Job::ePlaningTest, "����������� ������������" },
        { Job::ePaySallory,  "��������� ��������" },
        { Job::eReporting,   "���������� �����" },
        { Job::eVacation,    "���� � ������" },
        { Job::eCleaning,    "������� ������� �����" },
    };
    return m_jobMap.at(job);
}

