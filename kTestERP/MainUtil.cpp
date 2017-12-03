#include "stdafx.h"

#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include <windows.h>

#include "MainUtil.h"

#include "MainMenu.h"

int get_code() {
    SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
    int code = _getch();
    SetConsoleCP(866);// ��������� ������� �������� cp 866 � ����� �����
    if (code >= '�' && code <= '�') {
        code -= '�' - '�';
    }
    if (code >= 'a' && code <= 'z') {
        code -= 'a' - 'A';
    }
    return code;
}


MainUtil::MainUtil(bool verbose, const std::string& csvFolder) :
    m_csvFolder(csvFolder), m_verbose(verbose) {
}

void MainUtil::loadDataFromDir() {
    Company company;
    CSVReader(company, m_csvFolder, m_verbose);
    std::cout << "�������� ������ ���������. ������� �� ����� ������� ��� �����������.\n";
    get_code();
    std::swap(company, m_company);
}

void MainUtil::run() {
    loadDataFromDir();
    MainMenu mainMenu(this);
    mainMenu.run();
}

void MainUtil::doJob(Job job, IUnit* unit) {
    StringList report;
    bool res = unit->doJob(job, report);
    //std::time_t t = std::time(nullptr);
    //std::stringstream buffer;
    //struct tm buf;
    //localtime_s(&t, &buf);
    //buffer << std::put_time(buf, "%c %Z '");
    //std::string msg = buffer.str();
    // ��� ������ ������ "���������/�����/�����"
    //assert(!"��� ������ ���� ����/����� �������");

    //std::string msg = "����� � ���������� ������ �� ����������� �������: ";
    //msg.append(kind_to_str(unit->kind()));
    //msg.append(" '");
    //msg.append(unit->name());
    //msg.append("'\n���������� ������: ");
    //msg.append(job_to_str(job));


    //m_report.emplace_back(msg, report);

    std::swap(m_report, report);
}

void MainUtil::showLastReport() const noexcept{
    system("cls");
    if (m_report.empty()) {
        std::cout << "������� ���\n";
    }
    else {
        for (auto s : m_report) {
            std::cout << s << std::endl;
        }
    }

}
