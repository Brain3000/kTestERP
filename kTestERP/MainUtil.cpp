#include "stdafx.h"
#include "MainUtil.h"


void MainUtil::loadDataFromDir(const std::string csvFolder)
{
    CSVReader(m_company, csvFolder, m_verbose);
}

void MainUtil::run()
{
    // Not implemented yet;
    assert(false);
}
