#include "stdafx.h"
#include "CSVReader.h"

#include <iostream>

#include <boost/system/system_error.hpp>

namespace sys = boost::system;

const char kCSVExtension[] = ".csv";

CSVReader::CSVReader(const std::string path, bool verbose) throw(CSVReaderException):
    m_verbose(verbose) {
    if (m_verbose) {
        std::cout << "������ ������� � �������� �������: "
            << path << std::endl;
    }

    readFolder(path);
}

void CSVReader::readFolder(const std::string& path) throw(CSVReaderException) {
    try {
        m_path = fs::path(path);
        if (!fs::exists(m_path)) {
            throw CSVReaderException(m_path.string() + " �� ����������");
        }
        if (!fs::is_directory(m_path)) {
            throw CSVReaderException(m_path.string() + " �� �������� ���������");
        }
        fs::perms perm = fs::status(m_path).permissions();
        if (!(perm & fs::perms::others_read)) {
            throw CSVReaderException(m_path.string() + " ��� ���� �� ������");
        }
        fs::recursive_directory_iterator end_itr;
        for (fs::recursive_directory_iterator itr(m_path); itr != end_itr; ++itr) {
            // If it's not a directory, list it. If you want to list directories too, just remove this check.
            if (fs::is_regular_file(itr->path()) &&
                itr->path().extension().string() == kCSVExtension) {
                // assign current file name to current_file and echo it out to the console.
                if (m_verbose) {
                    std::string current_file = itr->path().string();
                    std::cout << "������� ��������� ���������� �� �����: "
                              << current_file << std::endl;
                }
            }
        }
    }
    catch (const sys::system_error& ex) {
        throw CSVReaderException(ex.what());
    }
}