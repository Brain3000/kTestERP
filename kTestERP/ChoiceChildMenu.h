#pragma once

#include <assert.h>

#include "CustomMenu.h"

template<typename T>
class ChoiceChildMenu :
    public CustomMenu {
public:
    ChoiceChildMenu(MainUtil* mainUtil, const T* object);
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
    virtual void runOption(const CustomMenu::Option& opt) {
        m_resultString = opt.m_additionalParam;
        if (opt.m_keyCode == ' ') {
            m_initOptionNum += 9;
        }
        if (m_initOptionNum >= m_scrolledOptions.size()) {
            m_initOptionNum = 0;
        }
    }
    CustomMenu::Options options() const;

private:
    Options m_scrolledOptions;
    const T* m_object;
    size_t m_initOptionNum = 0;
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
        m_scrolledOptions.emplace(m_object->child(it)->name(), initKeyCode++, OptionAction::eRunItemAndExit, m_object->child(it)->name());
    }
    //m_options.emplace("Ввести название раздела вручную", '0', OptionAction::eInputString, "Введите название раздела");
}

template<typename T>
CustomMenu::Options ChoiceChildMenu<T>::options() const {
    Options optToRet;
    char initialKey = '1';
    for (Options::const_iterator it = std::next(m_scrolledOptions.begin(), m_initOptionNum);
         it != m_scrolledOptions.end() && (initialKey <= '9'); ++it, ++initialKey) {
        optToRet.emplace(it->m_caption, initialKey, OptionAction::eRunItemAndExit, it->m_additionalParam);
    }
    if (m_scrolledOptions.size() > 9) {
        optToRet.emplace("Еще результаты...", ' ', OptionAction::eRunItem);
    }
    optToRet.insert(m_options.begin(), m_options.end());
    return optToRet;
}
