#pragma once

#include "CSVReader.h"

class MainUtil
{
public:
    MainUtil(bool verbose, const std::string& csvFolder);
    void loadDataFromDir();
    void run();
    void doJob(Job job, const IUnit* init);

private:
    const std::string m_csvFolder;
    Company m_company;
    bool m_verbose;

private:
    using Report = std::list<std::pair<std::string, StringList>>;
    Report m_report;
};

