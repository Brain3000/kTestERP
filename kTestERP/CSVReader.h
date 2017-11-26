#pragma once

#include <string>

#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>

namespace b = boost;
namespace sys = b::system;

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
    using IdsList = std::list<std::pair<std::string, int>>;
    using Tokenizer = b::tokenizer<b::char_separator<char>>;
public:
    CSVReader(const std::string path, bool verbose) throw(CSVReaderException);
    //const Departaments& depts() const { return m_depts; }

private:
    void readFolder(const std::string& path) throw(CSVReaderException);
	void readFile(const std::string& fileName) throw(CSVReaderException);
    IdsList getIdsList(const std::string& firstFileLine,
                         const std::string& fileName) noexcept;
private:
    bool m_verbose;
    fs::path m_path;
    //Departaments m_depts;
    const b::char_separator<char> m_sep;

};

