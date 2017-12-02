#include "stdafx.h"

#include "ChoiceDeptMenu.h"
#include "MainUtil.h"
#include "Company.h"

ChoiceDeptMenu::ChoiceDeptMenu(MainUtil* mainUtil, const std::string& caption) :
    MenuBase(mainUtil, "�������� ����� ��� ���������� ������ � �������� " + caption) {
    const Company& company(m_mainUtil->getCompany());
    const Company::Children& children(company.getChildren());
    assert(!children.empty());
    uint8_t initKeyCode = '1';
    for (auto it = children.begin(); it != children.end(); ++it) {
        m_options.emplace(company.child(it)->name(), initKeyCode++, OptionAction::eRunItemAndExit, company.child(it)->name());
    }
    m_options.emplace("������ �������� ������� �������", '0', OptionAction::eInputString, "������� �������� �������");
}

void ChoiceDeptMenu::runOption(const MenuBase::Option& opt) {
    m_resultString = opt.m_additionalParam;
}
