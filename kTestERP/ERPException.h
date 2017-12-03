/**
\file
\brief ������������� ����������, �������� ����������.
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include <exception>

/// ������������� ����������, ���������� �������� ������ ��� �������� csv.
class ERPException : public std::exception
{
    public:
        ERPException(std::string message) :
            std::exception(message.c_str())
            {}
};
