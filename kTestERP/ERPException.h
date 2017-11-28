#pragma once

#include <exception>

class ERPException : public std::exception
{
    public:
        ERPException(std::string message) :
            std::exception(message.c_str())
            {}
};
