/**
\file
\brief ������� ����.
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include "BaseMenu.h"

class IUnit;
/// ������� ����.
class MainMenu :
    public BaseMenu
{
public:
    /// �����������, ���������� ������ ����.
    MainMenu(MainUtil* mainUtil);

private:
    /// ��������� ������� ����.
    virtual void runOption(const Option& opt);

    /// ��������� ������ �������� ������.
    void taskToCompany(const CustomMenu::Option& opt);
    /// ������� ����� � ��������� ��� ������.
    void taskToDepartament(const CustomMenu::Option& opt);
    /// ������� �����, ���������� � ��������� ��� ������.
    void taskToEmployer(const CustomMenu::Option& opt);
    /// ������� ����� (�����/�����/���������).
    void reporting();
    /// ������ ������ �� ������ ��������� ����������� �������.
    void doJob(const std::string& jobName, IUnit* unit);    
};

