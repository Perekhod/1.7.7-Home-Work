#pragma once
#include <limits>
#include <initializer_list>
#include <iostream>
#include <string>
#include <cmath>
#include <exception>
#include "BadRange.h"
#include "BadLength.h"

class IntArray
{
public:
    IntArray();
    IntArray(int length);
    IntArray(const IntArray& other);
    IntArray(const std::initializer_list<int>& l);

    ~IntArray();

    void erase();

    int& operator[](int index);

 // Оператор присваивания, присваивает объект IntArray другому, возвращая ссылку на самого себя
    IntArray& operator=(const IntArray& other);

    int getLength() const;

 // reallocate изменяет размер массива. Все существующие элементы уничтожаются. Функция работает быстро.
    void reallocate(int newLenght);
    void resize(int newLength);

    void insertBefore(int value, int index);
    void insertToBeginning(int value);
    void insertToEnd(int value);

    void remove(int index);

    bool find(int value, size_t& index_result);

    void show() const;

private:
    int _length;
    int* _data;
};