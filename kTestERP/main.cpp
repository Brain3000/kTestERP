// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        po::options_description options("Allowed options");
        options.add_options()
            ("help,h", "produce help message")
            ("version,v", "version of application")
            ("verbose", "addition messages")
            ("input-calalog", po::value<std::string>(), "input catalog")
            ;

        po::variables_map vm;
        po::positional_options_description positional;
        positional.add("input-calalog", 1);
        po::store(po::command_line_parser(argc, argv).
                            options(options).
                            positional(positional).
                            run(),
                  vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            //std::cout << desc << std::endl;
            options.print(std::cout);
            return 0;
        }
        if (vm.count("version"))
        {
            std::cout << "Test ERP 1.0" << std::endl;
            return 0;
        }

        if (vm.count("input-calalog"))
        {
            std::cout << "Input calalog is: "
                      << vm["input-calalog"].as<std::string>() << std::endl;
        }

        if (vm.empty())
        {
            std::cout << options << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Exception of unknown type!\n";
        return 1;
    }
    return 0;
}



// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

//#include <boost/program_options.hpp>
//
//using namespace boost;
//namespace po = boost::program_options;
//
//#include <iostream>
//#include <algorithm>
//#include <iterator>
//using namespace std;
//
//int main(int ac, char* av[])
//{
//    try {
//        po::options_description desc("Allowed options");
//        desc.add_options()
//            ("help", "produce help message")
//            ("input-file", po::value<string>(), "input file")
//            ;
//
//        po::positional_options_description p;
//        p.add("input-file", -1);
//
//        po::variables_map vm;
//        po::store(po::command_line_parser(ac, av).
//            options(desc).positional(p).run(), vm);
//        po::notify(vm);
//
//        if (vm.count("help")) {
//            cout << "Usage: options_description [options]\n";
//            cout << desc;
//            return 0;
//        }
//
//        if (vm.count("input-file"))
//        {
//            cout << "Input files are: "
//                << vm["input-file"].as<string>() << "\n";
//        }
//    }
//    catch (std::exception& e)
//    {
//        cout << e.what() << "\n";
//        return 1;
//    }
//    return 0;
//}
