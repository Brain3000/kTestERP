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

CSVReader::CSVReader(Company& company, const std::string path, bool verbose) :
    m_company(company),
    m_verbose(verbose),
    m_sep(";", "", boost::keep_empty_tokens) {
    if (m_verbose) {
        std::cout << "������ ������� � �������� �������: '"
                  << path << "'\n";
    }

    readFolder(path);
}

void CSVReader::readFolder(const std::string& path) {
    try {
        m_path = path;

		//std::cout << fs::current_path().string() << std::endl;

        if (!fs::exists(m_path)) {
            throw ERPException("���� '" + m_path.string() + "' �� ����������");
        }
        if (!fs::is_directory(m_path)) {
            throw ERPException("���� '" + m_path.string() + " �� �������� ���������");
        }
        fs::perms perm = fs::status(m_path).permissions();
        if (!(perm & fs::perms::others_read)) {
            throw ERPException("������� '" + m_path.string() + "' �� ����� ���� �� ������");
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
		std::cout << "������� ��������� ���������� �� �����: '"
			<< fileName << "'\n";
	}
	// ��������� ����� �� ����, �� ��� ��������� �� ����������
	std::ifstream iStream(fileName);
    //iStream.imbue(std::locale("ru_RU.CP1251"));
    //iStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    std::string buf;
	if (!iStream.good()) {
		if (m_verbose) {
			std::cout << "�� ������� ������� ���� '" << fileName << "'\n";
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
								       "������ � ����������\n";
			}
            continue;
		}
        const std::string name = *(std::next(tokenizer.begin(), idsMap[kNameId]));
        const std::string posAsText = *(std::next(tokenizer.begin(), idsMap[kPositionId]));
        if (m_verbose) {
            std::cout << "������� ��������� ������ ���������� �� ������ "
                      << strIdx << " ��� ���������� '" << name
                      << "', ������������� '" << posAsText << "'\n";
        }
        IEmployerPtr empl = factory.createEmployer(name, posAsText);
        if (m_verbose && empl) {
            std::cout << "���������� � ���������� ������� �������\n";
        }

        if (empl && dept.addEmployer(empl)) {
            ++emplAdded;
            if (m_verbose) {
                std::cout << "��������� " << name << " �� �������������� "
                          << posAsText << " ������� �������� � ����� "
                          << deptName << std::endl;
            }
        }
	}
    if (m_verbose)
    {
        std::cout << "���������� " << strIdx << " ����� ����� '"
                  << fileName << "' ��������� " << emplAdded << " ����������� � ����� '"
                  << deptName << "', ����� � ������ "
                  << dept.getChild().size() << " �����������\n";
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
                std::cout << "� ����� '" /*<< fileName*/ << "' �� "
                             "��������� ������������� '" << idIt->first << "'\n";
            }
			idsMap.clear();
            break;
        }
        idIt->second = std::distance(tokenizer.begin(), tokIt);
    }
	return idsMap;
}
