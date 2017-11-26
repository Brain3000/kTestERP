#include "stdafx.h"
#include "CSVReader.h"

#include <iostream>
#include <fstream>

#include <boost/system/system_error.hpp>

const char kCSVExtension[] = ".csv";
const std::string kNameId = "�������";
const std::string kPositionId = "�������������";

CSVReader::CSVReader(const std::string path, bool verbose) throw(CSVReaderException):
    m_verbose(verbose), m_sep(";") {
    if (m_verbose) {
        std::cout << "������ ������� � �������� �������: "
            << path << std::endl;
    }

    readFolder(path);
}

void CSVReader::readFolder(const std::string& path) throw(CSVReaderException) {
    try {
        m_path = path;

		//std::cout << fs::current_path().string() << std::endl;

        if (!fs::exists(m_path)) {
            throw CSVReaderException("���� '" + m_path.string() + "' �� ����������");
        }
        if (!fs::is_directory(m_path)) {
            throw CSVReaderException("���� '" + m_path.string() + " �� �������� ���������");
        }
        fs::perms perm = fs::status(m_path).permissions();
        if (!(perm & fs::perms::others_read)) {
            throw CSVReaderException("������� '" + m_path.string() + "' �� ����� ���� �� ������");
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
		std::cout << "������� ��������� ���������� �� �����: '"
			<< fileName << "'\n";
	}
	// ��������� ����� �� ����, �� ��� ��������� �� ����������
	std::ifstream iStream(fileName);
	std::string buf;
	if (!iStream.good()) {
		if (m_verbose) {
			std::cout << "�� ������� ������� ���� '" << fileName << "'\n";
		}
		return;
	}
    IdsList idsList;
	while (getline(iStream, buf)) {
		//Tokenizer tokenizer(buf, sep);
		// ���� ���������� ������� ������ ����� (���� �����)
		if (idsList.empty()) {
            idsList = getIdsList(buf, fileName);
		}
        if (idsList.empty())
            return;
	}
}

CSVReader::IdsList CSVReader::getIdsList(const std::string& firstFileLine,
                                           const std::string& fileName) noexcept
{
    IdsList idsList{
        { kNameId, -1 },
        { kPositionId, -1 }
    };
    Tokenizer tokenizer(firstFileLine, m_sep);
    for (auto idIt = idsList.begin(); idIt != idsList.end(); ++idIt) {
        const auto tokIt = std::find(tokenizer.begin(), tokenizer.end(), idIt->first);
        if (tokIt == tokenizer.end()) {
            if (m_verbose) {
                std::cout << "� ����� '" << fileName << "' �� "
                    "��������� ������������� '" << idIt->first << "'\n";
            }
            idsList.clear();
            break;
        }
        idIt->second = std::distance(tokenizer.begin(), tokIt);
    }
    return idsList;
}
