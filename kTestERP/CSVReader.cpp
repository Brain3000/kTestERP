#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <codecvt>

#include <boost/system/system_error.hpp>

#include "CSVReader.h"
#include "ERPException.h"

const char kCSVExtension[] = ".csv";
const std::string kNameId = "Фамилия";
const std::string kPositionId = "Специальность";

const CSVReader::IdsMap CSVReader::s_idsMap {
	{ kNameId, -1 },
	{ kPositionId, -1 }
};

CSVReader::CSVReader(Company& company, const std::string path, bool verbose) :
    m_company(company),
    m_verbose(verbose),
    m_sep(";", "", boost::keep_empty_tokens) {
    if (m_verbose) {
        std::cout << "Указан каталог с входными файлами: '"
                  << path << "'\n";
    }

    readFolder(path);
}

void CSVReader::readFolder(const std::string& path) {
    try {
        m_path = path;

		//std::cout << fs::current_path().string() << std::endl;

        if (!fs::exists(m_path)) {
            throw ERPException("Путь '" + m_path.string() + "' не существует");
        }
        if (!fs::is_directory(m_path)) {
            throw ERPException("Путь '" + m_path.string() + " не является каталогом");
        }
        fs::perms perm = fs::status(m_path).permissions();
        if (!(perm & fs::perms::others_read)) {
            throw ERPException("Каталог '" + m_path.string() + "' не имеет прав на чтение");
        }
        fs::recursive_directory_iterator end_itr;
        for (fs::recursive_directory_iterator itr(m_path); itr != end_itr; ++itr) {
            // If it's not a directory, list it. If you want to list directories too, just remove this check.
            if (fs::is_regular_file(itr->path()) &&
                itr->path().extension().string() == kCSVExtension) {
				readFile(itr->path().string(), itr->path().stem().string());
            }
        }
    }
    catch (const sys::system_error& ex) {
        throw ERPException(ex.what());
    }
}

void CSVReader::readFile(const std::string& fileName,
						 const std::string& deptName) {
	if (m_verbose) {
		std::cout << "Попытка прочитать информацию из файла: '"
			<< fileName << "'\n";
	}
	// Закрывать поток не буду, бо сам закроется на диструкции
	std::ifstream iStream(fileName);
    //iStream.imbue(std::locale("ru_RU.CP1251"));
    //iStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    std::string buf;
	if (!iStream.good()) {
		if (m_verbose) {
			std::cout << "Не удалось открыть файл '" << fileName << "'\n";
		}
		return;
	}
    Departament& dept(m_company.getOrCreateDept(deptName));
    EmployerFactory factory(m_verbose);
    IdsMap idsMap;
	int maxIdx(-1), strIdx(0), emplAdded(0);
    
    //using convert_type = std::codecvt_utf8<wchar_t>;
    //static std::wstring_convert<convert_type, wchar_t> converter;

	while (getline(iStream, buf)) {
		++strIdx;
        //std::string buf = converter.to_bytes(wbuf);
		// Надо определить индексы нужных полей (если будут)
		if (idsMap.empty()) {
			idsMap = getIdsMap(buf, fileName);
			if (idsMap.empty()) {
				return;
			}
			maxIdx = std::max_element(idsMap.begin(),
									  idsMap.end(),
									  [](const IdPair& p1, const IdPair& p2)
									  { return p1.second < p2.second; })->second;
			continue;
		}
		// Индексы идентификаторов получены, начинаем извлекать данные
		Tokenizer tokenizer(buf, m_sep);
		if (std::distance(tokenizer.begin(), tokenizer.end()) <= maxIdx) {
			if (m_verbose) {
				std::cout << "В строке " << strIdx << " менее "
						  << maxIdx << " элементов, поэтому из неё нельзя извлечь "
								       "данные о сотруднике\n";
			}
            continue;
		}
        const std::string name = *(std::next(tokenizer.begin(), idsMap[kNameId]));
        const std::string posAsText = *(std::next(tokenizer.begin(), idsMap[kPositionId]));
        if (m_verbose) {
            std::cout << "Попытка загрузить данные сотрудника из строки "
                      << strIdx << " имя сотрудника '" << name
                      << "', специальность '" << posAsText << "'\n";
        }
        IEmployerPtr empl = factory.createEmployer(name, posAsText);
        if (m_verbose && empl) {
            std::cout << "Информация о сотруднике успешно создана\n";
        }

        if (empl && dept.addEmployer(empl)) {
            ++emplAdded;
            if (m_verbose) {
                std::cout << "Сотрудник " << name << " со специальностью "
                          << posAsText << " успешно добавлен в отдел "
                          << deptName << std::endl;
            }
        }
	}
    if (m_verbose)
    {
        std::cout << "Обработано " << strIdx << " строк файла '"
                  << fileName << "' добавлено " << emplAdded << " сотрудников в отдел '"
                  << deptName << "', всего в отделе "
                  << dept.getChild().size() << " сотрудников\n";
    }
}

CSVReader::IdsMap CSVReader::getIdsMap(const std::string& firstFileLine,
                                         const std::string& fileName) noexcept
{
	IdsMap idsMap = s_idsMap;
    Tokenizer tokenizer(firstFileLine, m_sep);
    for (auto idIt = idsMap.begin(); idIt != idsMap.end(); ++idIt) {
        const auto tokIt = std::find(tokenizer.begin(), tokenizer.end(), idIt->first);
        if (tokIt == tokenizer.end()) {
            if (m_verbose) {
                std::cout << "В файле '" /*<< fileName*/ << "' не "
                             "обнаружен идентификатор '" << idIt->first << "'\n";
            }
			idsMap.clear();
            break;
        }
        idIt->second = std::distance(tokenizer.begin(), tokIt);
    }
	return idsMap;
}
