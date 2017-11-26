#include "stdafx.h"
#include "CSVReader.h"

#include <iostream>

#include <boost/system/system_error.hpp>

namespace sys = boost::system;


CSVReader::CSVReader(const std::string path, bool verbose) throw(CSVReaderException):
    m_verbose(verbose)
{
    if (m_verbose)
    {
        std::cout << "������ ������� � �������� �������: "
            << path << std::endl;
    }
    try
    {
        m_path = fs::path(path);
        if (!fs::exists(m_path))
        {
            throw CSVReaderException(m_path.string() + " �� ����������");
        }
        if (!fs::is_directory(m_path))
        {
            throw CSVReaderException(m_path.string() + " �� �������� ���������");
        }
        fs::perms perm = fs::status(m_path).permissions();
        if (!(perm & fs::perms::others_exe && perm & fs::perms::others_write))
        {
            throw CSVReaderException(m_path.string() + " ��� ���� �� ������");
        }
    }
    catch (const sys::system_error& ex)
    {
        throw CSVReaderException(ex.what());
    }
}
