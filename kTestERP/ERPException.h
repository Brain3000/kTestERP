/**
\file
\brief Специфическое исключение, кидаемое программой.
\author Leontyev George
\version 1.0
\date Ноябрь 2017
*/
#pragma once

#include <exception>

/// Специфическое исключение, фактически кидается только при загрузке csv.
class ERPException : public std::exception
{
    public:
        ERPException(std::string message) :
            std::exception(message.c_str())
            {}
};
