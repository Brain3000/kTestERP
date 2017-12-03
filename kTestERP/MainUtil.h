/**
\file
\brief ������� �������.
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include "CSVReader.h"
/**
���� ������ �������, ���������� � ����������. 
��� ���� - �������� ������ � �������� �������� ���
�������� � ���������
*/
int get_code();

/**
    \brief ������� �������, ������� ����������� � �����,
    ��������� � �� ������ �� csv-������, ��������� ������� ����
    � ��������� ������ ����, ������ ������ ��������������, 
    ������� ������.
*/
class MainUtil
{
public:
    /**
    \brief ����������� � �����������
    \param[in] verbose - �������� ���������� ��������� (��� �������� csv).
    \param[in] csvFolder - ���� � �������� � csv-�������.
    ��� �������� ������� ����� ������������� �����������.
    */
    MainUtil(bool verbose, const std::string& csvFolder);

    /// ������� ����� �������. ��������� � �� ����������.
    void run();

    /**
    \brief ���� ������ �� ���������� ������ ��������� ����������� �������.
    \param[in] job - ��� �����.
    \param[in] unit - ����������� �������, ������� ������ ��������� ������ � �
    ������� ���� ������� �����.
    */
    void doJob(Job job, IUnit* unit);

    /// ������� ���������� � ��������. ����� ��� ������ ����.
    Company& getCompany() noexcept {
        return m_company;
    }
    /// ������� ������ ����� �� �����.
    void showLastReport() const noexcept;

private:
    void loadDataFromDir();

private:
    const std::string m_csvFolder;
    Company m_company;
    bool m_verbose;

private:
    StringList m_report;
};

