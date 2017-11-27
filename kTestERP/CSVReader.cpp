#include "stdafx.h"
#include "CSVReader.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <codecvt>

#include <boost/system/system_error.hpp>

const char kCSVExtension[] = ".csv";
const std::wstring kNameId = L"Фамилия";
const std::wstring kPositionId = L"Специальность";

const CSVReader::IdsMap CSVReader::s_idsMap {
	{ kNameId, -1 },
	{ kPositionId, -1 }
};

CSVReader::CSVReader(const std::string path, bool verbose) :
    m_verbose(verbose), m_sep(L";") {
    if (m_verbose) {
        std::cout << "Указан каталог с входными файлами: "
            << path << std::endl;
    }

    readFolder(path);
}

void CSVReader::readFolder(const std::string& path) {
    try {
        m_path = path;

		//std::cout << fs::current_path().string() << std::endl;

        if (!fs::exists(m_path)) {
            throw CSVReaderException("Путь '" + m_path.string() + "' не существует");
        }
        if (!fs::is_directory(m_path)) {
            throw CSVReaderException("Путь '" + m_path.string() + " не является каталогом");
        }
        fs::perms perm = fs::status(m_path).permissions();
        if (!(perm & fs::perms::others_read)) {
            throw CSVReaderException("Каталог '" + m_path.string() + "' не имеет прав на чтение");
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
        throw CSVReaderException(ex.what());
    }
}

void CSVReader::readFile(const std::string& fileName,
						 const std::string& depName) {
	if (m_verbose) {
		std::cout << "Попытка прочитать информацию из файла: '"
			<< fileName << "'\n";
	}
	// Закрывать поток не буду, бо сам закроется на диструкции
	std::wifstream iStream(fileName);
    iStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    std::wstring buf;
	if (!iStream.good()) {
		if (m_verbose) {
			std::cout << "Не удалось открыть файл '" << fileName << "'\n";
		}
		return;
	}
    Departament& dept(getDepartamen(depName));
    EmployerFactory factory(m_verbose);
    IdsMap idsMap;
	int maxIdx(-1), strIdx(0);
	while (getline(iStream, buf)) {
		++strIdx;
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
								       "данные о сотруднике";
			}
            continue;
		}
        const std::wstring name = *(std::next(tokenizer.begin(), idsMap[kNameId]));
        const std::wstring posAsText = *(std::next(tokenizer.begin(), idsMap[kPositionId]));
        if (m_verbose) {
            std::wcout << L"Попытка загрузить данные сотрудника из строки "
                      << strIdx << L" имя сотрудника '" << name
                      << L"', специальность '" << posAsText << L"'\n";
        }
        IEmployerPtr empl = factory.createEmployer(name, posAsText);
        if (m_verbose && empl) {
            std::cout << "Информация о сотруднике успешно создана\n";
        }
        dept.addEmployer(empl);
	}
}

CSVReader::IdsMap CSVReader::getIdsMap(const std::wstring& firstFileLine,
                                         const std::string& fileName) noexcept
{
	IdsMap idsMap;
    Tokenizer tokenizer(firstFileLine, m_sep);
    for (auto idIt = idsMap.begin(); idIt != idsMap.end(); ++idIt) {
        const auto tokIt = std::find(tokenizer.begin(), tokenizer.end(), idIt->first);
        if (tokIt == tokenizer.end()) {
            if (m_verbose) {
                std::wcout << L"В файле '" /*<< fileName*/ << L"' не "
                              L"обнаружен идентификатор '" << idIt->first << L"'\n";
            }
			idsMap.clear();
            break;
        }
        idIt->second = std::distance(tokenizer.begin(), tokIt);
    }
	return idsMap;
}

Departament& CSVReader::getDepartamen(const std::string& deptName) {
    auto it = m_depts.find(deptName);
    if (it != m_depts.end())
        return it->second;
    auto p = m_depts.emplace(deptName, deptName);
    if (!p.second) {
        throw CSVReaderException("Не удалось добавить подразделение с именем " + deptName);
    }
    return p.first->second;
}
