#include "stdafx.h"

#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "MainUtil.h"

#include "MainMenu.h"

MainUtil::MainUtil(bool verbose, const std::string& csvFolder) :
    m_csvFolder(csvFolder), m_verbose(verbose) {
}

void MainUtil::loadDataFromDir() {
    Company company;
    CSVReader(company, m_csvFolder, m_verbose);
    std::cout << "�������� ������ ���������. ������� �� ����� ������� ��� �����������.\n";
    _getch();
    std::swap(company, m_company);
}

void MainUtil::run() {
    loadDataFromDir();
    MainMenu mainMenu(this);
    mainMenu.run();
}

void MainUtil::doJob(Job job, const IUnit* unit) {
    StringList report;
    bool res = unit->doJob(job, report);
    //std::time_t t = std::time(nullptr);
    //std::stringstream buffer;
    //struct tm buf;
    //localtime_s(&t, &buf);
    //buffer << std::put_time(buf, "%c %Z '");
    //std::string msg = buffer.str();
    // ��� ������ ������ "���������/�����/�����"
    assert(!"��� ������ ���� ����/����� �������");
    std::string msg = kind_to_str(unit->kind());
    msg.append("'");
    msg.append(unit->name());
    msg.append("' �������� ������: ");
    msg.append(job_to_str(job));
    msg.append("\n������ ");
    if (!res)
        msg.append("�� ");
    msg.append("���������");
    m_report.emplace_back(msg, report);
}
