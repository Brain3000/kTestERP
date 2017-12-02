#include "stdafx.h"

#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "MainUtil.h"

#include "Menu.h"

MainUtil::MainUtil(bool verbose, const std::string& csvFolder) :
    m_csvFolder(csvFolder), m_verbose(verbose) {
}

void MainUtil::loadDataFromDir() {
    CSVReader(m_company, m_csvFolder, m_verbose);
}

void MainUtil::run() {
    loadDataFromDir();
    std::cout << "�������� ������ ���������. ������� �� ����� ������� ��� �����������.\n";
    _getch();
    //Page mainPage(this, "������� ��������\n�������� ���� �� ������� ����:");
    //std::shared_ptr<MenuOptionBase> opt =
    //    std::make_shared<MenuOption>(&MainUtil::loadDataFromDir,
    //                                 &mainPage,
    //                                 "��������� csv-�����", '1');
    //mainPage.addOption(opt);
    ////mainPage.addOption(std::make_shared<MenuOption>(&MainUtil::loadDataFromDir,
    ////                                                &mainPage,
    ////                                                "��������� csv-�����", '1'));
    //mainPage.run();
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
    std::string msg = "���������� '";
    msg.append(unit->name());
    msg.append("' �������� ������: ");
    msg.append(job_to_str(job));
    msg.append("\n������ ");
    if (!res)
        msg.append("�� ");
    msg.append("���������");
    m_report.emplace_back(msg, report);
}
