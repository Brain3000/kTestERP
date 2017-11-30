// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/program_options.hpp>

#include "MainUtil.h"

const char kHelpOption[] = "help";
const char kVersionOption[] = "version";
const char kVerboseOption[] = "verbose";
const char kInputCatalogParam[] = "input-calalog";

// ��� ���������� namespace
namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        setlocale(LC_ALL, "Russian");
        po::options_description options("��������� ���������");
        options.add_options()
            ("help,h", "����� ���������")                                   // ����� ������
            ("version,v", "����������� ������ ����������")                  // ����� ������ ������
            ("verbose", "�������������� ��������� (��� ������ cvs)")        // ����� �������������� ���������
                                                                            // ��� �������� csv
            // ����������� �������� - ������� � csv
            (kInputCatalogParam, po::value<std::string>(), "������� � �������� "
				"������� cvs (��� ������ ��������� ���� �������� ���� ��������� �����������)");

        po::variables_map vm;
        po::positional_options_description positional;
        // ��������� ����������� ���������
        positional.add(kInputCatalogParam, 1);

        po::store(po::command_line_parser(argc, argv).
                            options(options).
                            positional(positional).
                            run(),
                  vm);
        po::notify(vm);

        // ���� ����������� ����� help
        if (vm.count(kHelpOption))
        {
            std::cout << options << std::endl;
#ifdef _DEBUG
            _getch();
#endif
            return 0;
        }
        // ���� ����������� ����� version
        if (vm.count(kVersionOption))
        {
            std::cout << "Test ERP 1.0" << std::endl;
#ifdef _DEBUG
            _getch();
#endif
            return 0;
        }

        if (vm.count(kInputCatalogParam))
        {
            MainUtil mainUtil(vm.count(kVerboseOption));
            std::string catalog = vm["input-calalog"].as<std::string>();
            mainUtil.loadDataFromDir(catalog);
            mainUtil.run();
        }
        else
        {
            std::cout << options << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << "������: " << e.what() << std::endl;
#ifdef _DEBUG
        _getch();
#endif
        return 1;
    }
    catch (...) {
        std::cerr << "���������� ������������ ����!\n";
        return 1;
    }
#ifdef _DEBUG
    _getch();
#endif
    return 0;
}
