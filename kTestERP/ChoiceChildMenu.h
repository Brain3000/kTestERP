/**
\file
\brief Реализация базового класса для меню выбора подчиненной структурной единицы
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include <assert.h>

#include "CustomMenu.h"

/**
\brief Реализация базового класса для меню выбора подчиненной структурной единицы
T - тип объекта, это тип объекта контейнера, из которого мы получим подчиненные объекты
и выберем один из них.

Класс создает и обслуживает меню выбора струкрурных единиц, которые могут входить в состав
других структурных единиц. Поскольку таких единиц может быть много - организован страничный вывод
таких элементов. Листаются страницы пробелом.
*/
template<typename T>
class ChoiceChildMenu :
    public CustomMenu {
public:
    /// Создает меню, в качестве пунктов меню - будут элементы контейнера object
    ChoiceChildMenu(MainUtil* mainUtil, const T* object);
    /// Возвращает выбранный элемент или пустой Ptr.
    typename T::ChildPtr result() const {
        T::ChildPtr res;
        if (!m_resultString.empty()) {
            res = m_object->childByName(m_resultString);
            // Как-так - имя есть, а структурной единицы нет?!
            assert(res);
        }
        return res;
    }

protected:
    /// Обработка выбора пункта меню. Если выбрано пролистывание,
    /// то меню перестраивается.
    virtual void runOption(const CustomMenu::Option& opt) {
        m_resultString = opt.m_additionalParam;
        if (opt.m_keyCode == ' ') {
            m_initOptionNum += s_itemsPerPage;
        }
        if (m_initOptionNum >= m_scrolledOptions.size()) {
            m_initOptionNum = 0;
        }
    }
    /// Возвращает список доступных к этому моменту опций выбора.
    CustomMenu::Options options() const;

private:
    Options m_scrolledOptions;
    const T* m_object;
    size_t m_initOptionNum = 0;
    static const int s_itemsPerPage = 9;
};

template<typename T>
ChoiceChildMenu<T>::ChoiceChildMenu(MainUtil* mainUtil, const T* object) :
    CustomMenu(mainUtil, "Выберите структурную единицу для постановки задачи"),
    m_object(object) {
    assert(object);
    const T::Children& children(m_object->getChildren());
    assert(!children.empty());
    int initKeyCode = '1';
    for (auto it = children.begin(); it != children.end(); ++it) {
        m_scrolledOptions.emplace(m_object->child(it)->description(), initKeyCode++, OptionAction::eRunItemAndExit, m_object->child(it)->name());
    }
}

template<typename T>
CustomMenu::Options ChoiceChildMenu<T>::options() const {
    Options optToRet;
    char initialKey = '1';
    for (Options::const_iterator it = std::next(m_scrolledOptions.begin(), m_initOptionNum);
         it != m_scrolledOptions.end() && (initialKey <= '9'); ++it, ++initialKey) {
        optToRet.emplace(it->m_caption, initialKey, OptionAction::eRunItemAndExit, it->m_additionalParam);
    }
    if (m_scrolledOptions.size() > s_itemsPerPage) {
        std::string optCaption = "Еще результаты. Отображается страница [";
        optCaption.append(std::to_string(m_initOptionNum / s_itemsPerPage + 1));
        optCaption.append("/");
        optCaption.append(std::to_string((int)ceil((double)m_scrolledOptions.size()/(double)s_itemsPerPage)));
        optCaption.append("]");
        optToRet.emplace(optCaption, ' ', OptionAction::eRunItem);
    }
    optToRet.insert(m_options.begin(), m_options.end());
    return optToRet;
}
