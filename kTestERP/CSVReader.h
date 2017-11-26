#pragma once

#include <string>

#include <boost/filesystem.hpp>

#include "structures.h"

namespace fs = boost::filesystem;

class CSVReaderException : public std::exception
{
public:
    CSVReaderException(std::string message) :
        std::exception(message.c_str())
        {}
};

class CSVReader
{
public:
    CSVReader(const std::string path, bool verbose) throw(CSVReaderException);
    const Departaments& depts() const { return m_depts; }

private:
    void readFolder(const std::string& path) throw(CSVReaderException);
	void readFile(const std::string& fileName) throw(CSVReaderException);
private:
    bool m_verbose;
    fs::path m_path;
    Departaments m_depts;
};

