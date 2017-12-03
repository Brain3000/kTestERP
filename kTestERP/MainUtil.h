#pragma once

#include "CSVReader.h"

int get_code();

class MainUtil
{
public:
    //using Report = std::list<std::pair<std::string, StringList>>;

    MainUtil(bool verbose, const std::string& csvFolder);
    void loadDataFromDir();
    void run();
    void doJob(Job job, IUnit* init);
    Company& getCompany() noexcept {
        return m_company;
    }
    void showLastReport() const noexcept;

private:
    const std::string m_csvFolder;
    Company m_company;
    bool m_verbose;

private:
    StringList m_report;
};

