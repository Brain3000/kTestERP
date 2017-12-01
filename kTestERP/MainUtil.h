#pragma once

#include "CSVReader.h"

class MainUtil
{
public:
    MainUtil(bool verbose, const std::string& csvFolder);
    void loadDataFromDir();
    void run();

private:
    const std::string m_csvFolder;
    Company m_company;
    bool m_verbose;
};

