#pragma once
#include "MenuBase.h"
#include "assert.h"

template<typename T>
class ChoiceChildMenu :
    public MenuBase {
public:
    ChoiceChildMenu(MainUtil* mainUtil, const T* object);
    typename T::ChildPtr result() const {
        T::ChildPtr res;
        if (!m_resultString.empty()) {
            res = m_object->childByName(m_resultString);
            //  ак-так - им€ есть, а структурной единицы нет?!
            assert(res);
        }
        return res;
    }

protected:
    virtual void runOption(const MenuBase::Option& opt) {
        m_resultString = opt.m_additionalParam;
    }

private:
    const T* m_object;
};

template<typename T>
ChoiceChildMenu<T>::ChoiceChildMenu(MainUtil* mainUtil, const T* object) :
    MenuBase(mainUtil, "¬ыберите структурную единицу дл€ постановки задачи"),
    m_object(object) {
    const T::Children& children(m_object->getChildren());
    assert(!children.empty());
    uint8_t initKeyCode = '1';
    for (auto it = children.begin(); it != children.end(); ++it) {
        m_options.emplace(m_object->child(it)->name(), initKeyCode++, OptionAction::eRunItemAndExit, m_object->child(it)->name());
    }
    //m_options.emplace("¬вести название раздела вручную", '0', OptionAction::eInputString, "¬ведите название раздела");
}
