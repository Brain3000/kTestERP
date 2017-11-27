#pragma once

#include <string>

#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <map>

namespace b = boost;
namespace sys = b::system;

#include "Departament.h"

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
	using IdsMap = std::map<std::string, int>;
	using IdPair = IdsMap::value_type;
	using Tokenizer = b::tokenizer<b::char_separator<char>,
                                   std::string::const_iterator,
                                   std::string>;
public:
    CSVReader(const std::string path, bool verbose);
    //const Departaments& depts() const { return m_depts; }

private:
    void readFolder(const std::string& path);
	void readFile(const std::string& fileName,
				  const std::string& deptName);
	IdsMap getIdsMap(const std::string& firstFileLine,
                     const std::string& fileName) noexcept;
    Departament& getDepartamen(const std::string& deptName);
private:
    bool m_verbose;
    fs::path m_path;
    Departaments m_depts;
    const b::char_separator<char> m_sep;
	Departaments m_deps;
	static const IdsMap s_idsMap;
};

