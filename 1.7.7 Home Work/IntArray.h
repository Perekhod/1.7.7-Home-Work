#pragma once
#include <limits>
#include <initializer_list>
#include <iostream>
#include <string>
#include <cmath>
#include <exception>
#include "BadRange.h"
#include "BadLength.h"
#include <assert.h>

template <class T> class Array
{
private:
    int m_length;
    T* m_data;

public:
    Array()
    {
        m_length = 0;
        m_data = nullptr;
    }

    Array(int length)
    {
        m_data = new T[length];
        m_length = length;
    }

    ~Array()
    {
        delete[] m_data;
    }

    void Erase()
    {
        delete[] m_data;
        // Присваиваем значение nullptr для m_data, чтобы на выходе не получить висячий указатель!
        m_data = nullptr;
        m_length = 0;
    }

    T& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int getLength(); // определяем метод и шаблон метода getLength() ниже
};

template <typename T> int Array<T>::getLength() 
{ 
    return m_length; 
} 

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