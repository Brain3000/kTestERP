#pragma once

#include "CSVReader.h"

uint8_t get_code();

class MainUtil
{
public:
    using Report = std::list<std::pair<std::string, StringList>>;

    MainUtil(bool verbose, const std::string& csvFolder);
    void loadDataFromDir();
    void run();
    void doJob(Job job, const IUnit* init);
    const Company& getCompany() const noexcept {
        return m_company;
    }
    //const Report& report() const noexcept {
    //    return m_report;
    //}
    void showLastReport() const;

private:
    const std::string m_csvFolder;
    Company m_company;
    bool m_verbose;

private:
    Report m_report;
};

