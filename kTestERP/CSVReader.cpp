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

CSVReader::CSVReader(Company& company, const std::string& path, bool verbose) :
    m_company(company),
    m_verbose(verbose),
    m_sep(";", "", boost::keep_empty_tokens),
    m_factory(verbose) {
    readFolder(path);
}

void CSVReader::readFolder(const std::string& _path) {
    try {
        const fs::path path(fs::canonical(_path));
        if (m_verbose) {
            std::cout << "Указан каталог с входными файлами: '"
                << path.string() << "'\n";
        }

        if (!fs::exists(path)) {
            throw ERPException("Путь '" + path.string() + "' не существует");
        }
        if (!fs::is_directory(path)) {
            throw ERPException("Путь '" + path.string() + " не является каталогом");
        }
        fs::perms perm = fs::status(path).permissions();
        if (!(perm & fs::perms::others_read)) {
            throw ERPException("Каталог '" + path.string() + "' не имеет прав на чтение");
        }
        fs::recursive_directory_iterator end_itr;
        for (fs::recursive_directory_iterator itr(path); itr != end_itr; ++itr) {
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
    std::string buf;
	if (!iStream.good()) {
		if (m_verbose) {
			std::cout << "Не удалось открыть файл '" << fileName << "'\n";
		}
		return;
	}
    DepartamentPtr dept = m_company.getOrCreateDept(deptName);
    IdsMap idsMap;
	int maxIdx(-1), strIdx(0), emplAdded(0);
    
	while (getline(iStream, buf)) {
		++strIdx;
		// Надо определить индексы нужных полей (если будут)
        // Расчет на то, что в cvs-файле названия нужных полей будут не по порядку,
        // а в разнобой, да еще некоторых может и не быть.
        // Индесы нам нужны, чтобы из каждой строки извлекать значение нужного столбца,
        // если таковой столбец вообще есть.
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
        // Имя и текстовое представление должности для сотрудника.
        const std::string name = *(std::next(tokenizer.begin(), idsMap[kNameId]));
        const std::string posAsText = *(std::next(tokenizer.begin(), idsMap[kPositionId]));
        // Попробуем создать и добавить.
        if (addEmployer(strIdx, name, posAsText, dept.get())) {
            ++emplAdded;
        }
    }
    if (m_verbose)
    {
        std::cout << "Обработано " << strIdx << " строк файла '"
                  << fileName << "' добавлено " << emplAdded << " сотрудников в отдел '"
                  << deptName << "'\n";
    }
}

bool CSVReader::addEmployer(int strIdx,
                            const std::string& name,
                            const std::string& posAsText,
                            Departament* dept) {
    if (m_verbose) {
        std::cout << "Попытка загрузить данные сотрудника из строки "
            << strIdx << " имя сотрудника '" << name
            << "', специальность '" << posAsText << "'\n";
    }
    EmployerPtr empl = m_factory.createEmployer(name, posAsText);
    if (!empl) {
        if (m_verbose) {
            std::cout << "Сотрудник со специальностью '"
                      << posAsText << "' не был создан\n";
        }
        return false;
    }
    if (m_verbose) {
        std::cout << "Информация о сотруднике успешно создана\n";
    }

    if (!dept->addEmployer(empl)) {
        if (m_verbose) {
            std::cout << "Сотрудник с именем '" << name
                      << "' и должностью '" << posAsText
                      << "' не добавлен в отдел '"
                      << dept->name() << "' поскольку сотрудник "
                      "с такой должностью и именем в отделе уже есть\n";
        }
        return false;
    }

    if (m_verbose) {
        std::cout << "Сотрудник '" << name << "' со специальностью '"
                  << posAsText << "' успешно добавлен в отдел '"
                  << dept->name() << "'\n";
    }
    return true;
}

CSVReader::IdsMap CSVReader::getIdsMap(const std::string& firstFileLine,
                                       const std::string& fileName) noexcept {
	IdsMap idsMap = s_idsMap;
    Tokenizer tokenizer(firstFileLine, m_sep);
    for (auto idIt = idsMap.begin(); idIt != idsMap.end(); ++idIt) {
        const auto tokIt = std::find(tokenizer.begin(), tokenizer.end(), idIt->first);
        if (tokIt == tokenizer.end()) {
            if (m_verbose) {
                std::cout << "В файле '" << fileName << "' не "
                             "обнаружен идентификатор '" << idIt->first << "'\n";
            }
			idsMap.clear();
            break;
        }
        idIt->second = std::distance(tokenizer.begin(), tokIt);
    }
	return idsMap;
}
