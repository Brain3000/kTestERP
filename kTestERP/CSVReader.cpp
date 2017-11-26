#include "stdafx.h"
#include "CSVReader.h"

#include <iostream>

#include <boost/system/system_error.hpp>

namespace sys = boost::system;

const char kCSVExtension[] = ".csv";

CSVReader::CSVReader(const std::string path, bool verbose) throw(CSVReaderException):
    m_verbose(verbose) {
    if (m_verbose) {
        std::cout << "Указан каталог с входными файлами: "
            << path << std::endl;
    }

    readFolder(path);
}

void CSVReader::readFolder(const std::string& path) throw(CSVReaderException) {
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
				readFile(itr->path().string());
            }
        }
    }
    catch (const sys::system_error& ex) {
        throw CSVReaderException(ex.what());
    }
}

void CSVReader::readFile(const std::string& fileName) throw(CSVReaderException) {
	if (m_verbose) {
		std::cout << "Попытка прочитать информацию из файла: '"
			<< fileName << "'\n";
	}
}

