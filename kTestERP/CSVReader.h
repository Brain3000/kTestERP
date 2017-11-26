#pragma once

#include <string>

#include <boost/filesystem.hpp>

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

private:
    bool m_verbose;
    fs::path m_path;
};

