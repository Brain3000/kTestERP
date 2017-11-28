#pragma once

#include "CSVReader.h"

class MainUtil
{
public:
    MainUtil(bool verbose) : m_verbose(verbose) {}
    void loadDataFromDir(const std::string csvFolder);
    void run();

private:
    Company m_company;
    bool m_verbose;
};

