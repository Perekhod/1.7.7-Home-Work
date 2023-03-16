#pragma once
#include <exception>

class BadRange : public std::exception 
{
public:
    BadRange() = default;

    virtual const char* what() const noexcept override 
    {
        return "ОШИБКА: Вне диапазона массива.\n";
    }
};