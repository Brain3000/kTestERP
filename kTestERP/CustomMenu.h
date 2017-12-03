/**
\file
\brief Базовые вещи для всех меню
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include <string>
#include <set>
#include <memory>

class MainUtil;

/// Константа для пустой строки.
const std::string kEmptyString;

/**
    \brief Базовый класс для всех меню.

    Содержит возможные для меню типы опций и сам класс - описание опций
*/
class CustomMenu {
protected:
    /// Типы опций меню.
    enum class OptionAction {
        eExit,          ///< Ничего не делать, выйти из меню.
        eRunItem,       ///< Выполнить функцию runOption и перерисовать меню.
        eRunItemAndExit,///< Выполнить функцию runOption и выйти из меню.
    };

    /// Структура, реализующая элемент меню
    struct Option {
        Option(const std::string& cap,                      ///< Текст пункта меню.
               int keyCode,                                 ///< Код пункта меню (клавиша, на которую можно нажать)
               OptionAction action,                         ///< Действие при выборе пункта меню
               const std::string& addParam = kEmptyString); ///< Параметр, который может быть использован при срабатывании этого пункта меню.
        /// Напечатать представление пункта меню в консоли. Код клавиши будет напечатан в квадратных скобках.
        void show();                                        

        const std::string m_caption;        ///< Заголовок пункта меню.
        const int m_keyCode;                ///< Код (символ), который пользователь должен нажать, чтобы пункт меню выбрался.
        const OptionAction m_action;        ///< Действие при выборе пункта меню.
        const std::string m_additionalParam;///< Дополнительный параметр, может быть что угодно, используется как boost::variant

    private:
        /// Возвращает читаемое значение для ключа, например для ' ' возвращается слово Пробел.
        std::string printableKey() const;

    };

    /// Функтор для сравнения пункто меню (сравниваются по коду кнопки)
    struct OptionLess : std::binary_function<Option, Option, bool>  {
        bool operator()(const Option& op1, const Option& op2) const {
            return op1.m_keyCode < op2.m_keyCode;
        }
    };
    using Options = std::set<Option, OptionLess>;
public:
    virtual ~CustomMenu(){}
    /// Отобразить меню, ждать нажатия на клавиши и обрабатывать только те,
    /// которые заданы как ключи пунктов меню.
    void run();

    /// Возвращает m_additionalParam выбранного пукта меню. Может быть пустой строкой.
    const std::string& resultString() const noexcept {
        return m_resultString;
    }

protected:
    /**
        \brief Конструктор с параметрами - передается ссылка на главную
        утилиту и заголовок всего меню (или часть заголовка, в том случае
        если общие слова заголовка заданы в производном классе)
    */    
    CustomMenu(MainUtil* mainUtil, const std::string& caption);

    /**
        \brief     Вызывается при выборе пункта меню. Должна быть переопределена 
        в производных классах, как обработчик рекации на пункты меню.
        \param[int] сработавший пункт меню.
    */
    virtual void runOption(const Option& opt) = 0;

    /// Возвращает список всех опций.
    virtual Options options() const {
        return m_options;
    }

protected:
    MainUtil* m_mainUtil;
    const std::string m_caption;
    Options m_options;
    std::string m_resultString;
};

