#pragma once

#include <string>

#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <map>

#include "EmployerFactory.h"
#include "Company.h"

namespace b = boost;
namespace sys = b::system;
namespace fs = b::filesystem;


class CSVReader
{
	using IdsMap = std::map<std::string, int>;
	using IdPair = IdsMap::value_type;
	using Tokenizer = b::tokenizer<b::char_separator<char>,
                                   std::string::const_iterator,
                                   std::string>;
public:
    CSVReader(Company& company, const std::string& path, bool verbose);

private:
    void readFolder(const std::string& _path);
	void readFile(const std::string& fileName,
				  const std::string& deptName);

    bool addEmployer(int strIdx,
                     const std::string& name,
                     const std::string& posAsText,
                     Departament* dept);

    IdsMap getIdsMap(const std::string& firstFileLine,
                     const std::string& fileName) noexcept;
private:
    Company& m_company;
    bool m_verbose;
    const b::char_separator<char> m_sep;
	static const IdsMap s_idsMap;
    EmployerFactory m_factory;
};

