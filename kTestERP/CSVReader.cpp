#include "stdafx.h"
#include "CSVReader.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <codecvt>

#include <boost/system/system_error.hpp>

const char kCSVExtension[] = ".csv";
const std::wstring kNameId = L"�������";
const std::wstring kPositionId = L"�������������";

const CSVReader::IdsMap CSVReader::s_idsMap {
	{ kNameId, -1 },
	{ kPositionId, -1 }
};

CSVReader::CSVReader(const std::string path, bool verbose) :
    m_verbose(verbose), m_sep(L";") {
    if (m_verbose) {
        std::cout << "������ ������� � �������� �������: "
            << path << std::endl;
    }

    readFolder(path);
}

void CSVReader::readFolder(const std::string& path) {
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
		std::cout << "������� ��������� ���������� �� �����: '"
			<< fileName << "'\n";
	}
	// ��������� ����� �� ����, �� ��� ��������� �� ����������
	std::wifstream iStream(fileName);
    iStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    std::wstring buf;
	if (!iStream.good()) {
		if (m_verbose) {
			std::cout << "�� ������� ������� ���� '" << fileName << "'\n";
		}
		return;
	}
    Departament& dept(getDepartamen(depName));
    EmployerFactory factory(m_verbose);
    IdsMap idsMap;
	int maxIdx(-1), strIdx(0);
	while (getline(iStream, buf)) {
		++strIdx;
		// ���� ���������� ������� ������ ����� (���� �����)
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
		// ������� ��������������� ��������, �������� ��������� ������
		Tokenizer tokenizer(buf, m_sep);
		if (std::distance(tokenizer.begin(), tokenizer.end()) <= maxIdx) {
			if (m_verbose) {
				std::cout << "� ������ " << strIdx << " ����� "
						  << maxIdx << " ���������, ������� �� �� ������ ������� "
								       "������ � ����������";
			}
            continue;
		}
        const std::wstring name = *(std::next(tokenizer.begin(), idsMap[kNameId]));
        const std::wstring posAsText = *(std::next(tokenizer.begin(), idsMap[kPositionId]));
        if (m_verbose) {
            std::wcout << L"������� ��������� ������ ���������� �� ������ "
                      << strIdx << L" ��� ���������� '" << name
                      << L"', ������������� '" << posAsText << L"'\n";
        }
        IEmployerPtr empl = factory.createEmployer(name, posAsText);
        if (m_verbose && empl) {
            std::cout << "���������� � ���������� ������� �������\n";
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
                std::wcout << L"� ����� '" /*<< fileName*/ << L"' �� "
                              L"��������� ������������� '" << idIt->first << L"'\n";
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
        throw CSVReaderException("�� ������� �������� ������������� � ������ " + deptName);
    }
    return p.first->second;
}
