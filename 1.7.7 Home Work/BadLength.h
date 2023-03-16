#pragma once
#include <exception>

class BadLength : public std::exception 
{
public:
    BadLength() = default;

    virtual const char* what() const noexcept override 
    {
        return "������: ������������ ����� ���c���.\n";
    }
};