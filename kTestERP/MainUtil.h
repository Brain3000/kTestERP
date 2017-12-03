/**
\file
\brief Главная утилита.
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include "CSVReader.h"
/**
Ждет вывода символа, введенного с клавиатуры. 
Для букв - приводит символ к верхнему регистру для
латиницы и кириллицы
*/
int get_code();

/**
    \brief Главная утилита, владеет информацией о фирме,
    загружает в неё данные из csv-файлов, формирует главное меню
    и некоторые другие меню, задает работы подразделениям, 
    выводит отчеты.
*/
class MainUtil
{
public:
    /**
    \brief Конструктор с параметрами
    \param[in] verbose - выводить отладочные сообщения (при загрузке csv).
    \param[in] csvFolder - путь к каталогу с csv-файлами.
    При создании утилиты файлы автоматически загружаются.
    */
    MainUtil(bool verbose, const std::string& csvFolder);

    /// Главный метод утилиты. Запускает её на выполнение.
    void run();

    /**
    \brief Дать приказ на выполнение работы выбранной структурной единице.
    \param[in] job - вид работ.
    \param[in] unit - структурная единица, которая должна выполнить работу и у
    которой надо принять отчет.
    */
    void doJob(Job job, IUnit* unit);

    /// Вернуть информацию о компании. Нужно для других меню.
    Company& getCompany() noexcept {
        return m_company;
    }
    /// Вывести полный отчет по фирме.
    void showLastReport() const noexcept;

private:
    void loadDataFromDir();

private:
    const std::string m_csvFolder;
    Company m_company;
    bool m_verbose;

private:
    StringList m_report;
};

