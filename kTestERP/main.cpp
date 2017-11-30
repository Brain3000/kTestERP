// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/program_options.hpp>

#include "MainUtil.h"

const char kHelpOption[] = "help";
const char kVersionOption[] = "version";
const char kVerboseOption[] = "verbose";
const char kInputCatalogParam[] = "input-calalog";

// Для сокращения namespace
namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        setlocale(LC_ALL, "Russian");
        po::options_description options("Доступные параметры");
        options.add_options()
            ("help,h", "вывод подсказки")                                   // Опция помощи
            ("version,v", "отображение версии приложения")                  // Опция вывода версии
            ("verbose", "дополнительные сообщения (при чтении cvs)")        // Опция дополнительных сообщений
                                                                            // при загрузке csv
            // Позиционный параметр - каталог с csv
            (kInputCatalogParam, po::value<std::string>(), "каталог с входными "
				"файлами cvs (для работы программы этот параметр надо указывать обязательно)");

        po::variables_map vm;
        po::positional_options_description positional;
        // Добавляем позиционные параметры
        positional.add(kInputCatalogParam, 1);

        po::store(po::command_line_parser(argc, argv).
                            options(options).
                            positional(positional).
                            run(),
                  vm);
        po::notify(vm);

        // Если встретилась опция help
        if (vm.count(kHelpOption))
        {
            std::cout << options << std::endl;
#ifdef _DEBUG
            _getch();
#endif
            return 0;
        }
        // Если встретилась опция version
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
        std::cerr << "Ошибка: " << e.what() << std::endl;
#ifdef _DEBUG
        _getch();
#endif
        return 1;
    }
    catch (...) {
        std::cerr << "Исключение неизвестного типа!\n";
        return 1;
    }
#ifdef _DEBUG
    _getch();
#endif
    return 0;
}
