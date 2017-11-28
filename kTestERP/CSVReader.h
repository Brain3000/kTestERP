#pragma once

#include <string>

#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <map>

namespace b = boost;
namespace sys = b::system;

#include "Company.h"

namespace fs = boost::filesystem;


class CSVReader
{
	using IdsMap = std::map<std::string, int>;
	using IdPair = IdsMap::value_type;
	using Tokenizer = b::tokenizer<b::char_separator<char>,
                                   std::string::const_iterator,
                                   std::string>;
public:
    CSVReader(Company& company, const std::string path, bool verbose);

private:
    void readFolder(const std::string& path);
	void readFile(const std::string& fileName,
				  const std::string& deptName);
	IdsMap getIdsMap(const std::string& firstFileLine,
                     const std::string& fileName) noexcept;
private:
    Company& m_company;
    bool m_verbose;
    fs::path m_path;
    const b::char_separator<char> m_sep;
	static const IdsMap s_idsMap;
};

