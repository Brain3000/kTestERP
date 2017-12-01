#include "stdafx.h"

#include <memory>

#include "MainUtil.h"

#include "Menu.h"

MainUtil::MainUtil(bool verbose, const std::string& csvFolder) :
    m_csvFolder(csvFolder), m_verbose(verbose) {
}

void MainUtil::loadDataFromDir() {
    CSVReader(m_company, m_csvFolder, m_verbose);
}

void MainUtil::run() {
    loadDataFromDir();
    std::cout << "Загрузка данных завершена. Нажмите на любую клавишу для продолжения.\n";
    _getch();
    Page mainPage(this, "Главная страница\nВыберете один из пунктов меню:");
    std::shared_ptr<MenuOptionBase> opt =
        std::make_shared<MenuOption>(&MainUtil::loadDataFromDir,
                                     &mainPage,
                                     "Загрузить csv-файлы", '1');
    mainPage.addOption(opt);
    //mainPage.addOption(std::make_shared<MenuOption>(&MainUtil::loadDataFromDir,
    //                                                &mainPage,
    //                                                "Загрузить csv-файлы", '1'));
    mainPage.run();
}
