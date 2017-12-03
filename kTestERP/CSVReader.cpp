#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <codecvt>

#include <boost/system/system_error.hpp>

#include "CSVReader.h"
#include "ERPException.h"

const char kCSVExtension[] = ".csv";
const std::string kNameId = "�������";
const std::string kPositionId = "�������������";

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
            std::cout << "������ ������� � �������� �������: '"
                << path.string() << "'\n";
        }

        if (!fs::exists(path)) {
            throw ERPException("���� '" + path.string() + "' �� ����������");
        }
        if (!fs::is_directory(path)) {
            throw ERPException("���� '" + path.string() + " �� �������� ���������");
        }
        fs::perms perm = fs::status(path).permissions();
        if (!(perm & fs::perms::others_read)) {
            throw ERPException("������� '" + path.string() + "' �� ����� ���� �� ������");
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
    DepartamentPtr dept = m_company.getOrCreateDept(deptName);
    IdsMap idsMap;
	int maxIdx(-1), strIdx(0), emplAdded(0);
    
	while (getline(iStream, buf)) {
		++strIdx;
		// ���� ���������� ������� ������ ����� (���� �����)
        // ������ �� ��, ��� � cvs-����� �������� ������ ����� ����� �� �� �������,
        // � � ��������, �� ��� ��������� ����� � �� ����.
        // ������ ��� �����, ����� �� ������ ������ ��������� �������� ������� �������,
        // ���� ������� ������� ������ ����.
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
								       "������ � ����������\n";
			}
            continue;
		}
        // ��� � ��������� ������������� ��������� ��� ����������.
        const std::string name = *(std::next(tokenizer.begin(), idsMap[kNameId]));
        const std::string posAsText = *(std::next(tokenizer.begin(), idsMap[kPositionId]));
        // ��������� ������� � ��������.
        if (addEmployer(strIdx, name, posAsText, dept.get())) {
            ++emplAdded;
        }
    }
    if (m_verbose)
    {
        std::cout << "���������� " << strIdx << " ����� ����� '"
                  << fileName << "' ��������� " << emplAdded << " ����������� � ����� '"
                  << deptName << "'\n";
    }
}

bool CSVReader::addEmployer(int strIdx,
                            const std::string& name,
                            const std::string& posAsText,
                            Departament* dept) {
    if (m_verbose) {
        std::cout << "������� ��������� ������ ���������� �� ������ "
            << strIdx << " ��� ���������� '" << name
            << "', ������������� '" << posAsText << "'\n";
    }
    EmployerPtr empl = m_factory.createEmployer(name, posAsText);
    if (!empl) {
        if (m_verbose) {
            std::cout << "��������� �� �������������� '"
                      << posAsText << "' �� ��� ������\n";
        }
        return false;
    }
    if (m_verbose) {
        std::cout << "���������� � ���������� ������� �������\n";
    }

    if (!dept->addEmployer(empl)) {
        if (m_verbose) {
            std::cout << "��������� � ������ '" << name
                      << "' � ���������� '" << posAsText
                      << "' �� �������� � ����� '"
                      << dept->name() << "' ��������� ��������� "
                      "� ����� ���������� � ������ � ������ ��� ����\n";
        }
        return false;
    }

    if (m_verbose) {
        std::cout << "��������� '" << name << "' �� �������������� '"
                  << posAsText << "' ������� �������� � ����� '"
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
                std::cout << "� ����� '" << fileName << "' �� "
                             "��������� ������������� '" << idIt->first << "'\n";
            }
			idsMap.clear();
            break;
        }
        idIt->second = std::distance(tokenizer.begin(), tokIt);
    }
	return idsMap;
}
