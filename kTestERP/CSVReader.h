/**
\file
\brief Загрузчик csv - файлов.
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
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

/// Загрузчик информации о компании: отделах и сотрудниках
class CSVReader
{
	using IdsMap = std::map<std::string, int>;
	using IdPair = IdsMap::value_type;
	using Tokenizer = b::tokenizer<b::char_separator<char>,
                                   std::string::const_iterator,
                                   std::string>;
public:
    /**
    \brief Пытается загрузить информацию о компании.
    \param[out] company  информация о компании, в которую надо загрузить информацию
    \param[in] path путь начальной папки с csv-файлами.
    \param[in] verbose флаг того, что надо выводить отладочные сообщения при загрузке.
    \throw ERPException если путь не существует кинется исключение
    */
    CSVReader(Company& company, const std::string& path, bool verbose);

private:
    /// Читает каталог _path, каталог читается рекурсивно.
    void readFolder(const std::string& _path);
    /**
    \breif Читает информацию об отделе из файла.
    \param[in] fileName имя файла, который надо прочитать.
    Файл должен существовать и быть доступен для чтения.
    \param[in] deptName имя отдела, информация о котором загружается из файла.
    \throw ERPException - если файл не существует или нет доступа для чтения.
    */
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

