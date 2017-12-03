/**
\file
\brief ������������ ����� ������ � ������������� ��� ��������� �������
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include <unordered_set>

/// ������������ ����� �����, ������� ����� ��������� ����������� ������� �����
enum class Job {
    eProgramming,   ///< ���������������
    eProjecting,    ///< �������������    
    eTranslation,   ///< ���������� ������
    eTesting,       ///< �����������
    ePlaningTest,   ///< ���������� �������� �����
    ePaySallory,    ///< ��������� ��������
    eReporting,     ///< ���������� ����������� �����
    eVacation,      ///< ���� � ������
    eCleaning,      ///< ������ ������� �����

    eFirst = eProgramming,  ///< ������ � ��������� ������� ��� ������������
    eLast = eCleaning,
};

/// �������� ��������� ������������� ������
const std::string job_to_str(Job job);

/// �������� �������� ������������ �� ���������� �������������
/// ���� �� ������ �������� �������� ������������ ������, ��
/// �������� std::out_of_range
Job str_to_job(const std::string& jobName);

/// ������ ������ (������� �� ����� ��������)
using Jobs = std::unordered_set<Job>;

