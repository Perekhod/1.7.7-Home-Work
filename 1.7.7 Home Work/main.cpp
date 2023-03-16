#include <iostream>
#include "IntArray.h"

int main()
{
    setlocale(LC_ALL, "ru");

    std::cout << "1._________________________________\n";

    try 
    {
        IntArray arrOne(9999);
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "2._________________________________\n";

    try 
    {
        IntArray arrTwo(0);
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "3._________________________________\n";

    try 
    {
        IntArray arrThree{4, 43, 45 };
        std::cout << arrThree[10] << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "4._________________________________\n";

    try
    {
        IntArray arrFour(-10);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "5._________________________________\n";

    IntArray IntOne(10);            // Создать контейнер.
    IntOne.show();
    IntOne.insertBefore(10, 5);     // Вставить элемент в контейнер.
    IntOne.show();
    IntOne.insertToBeginning(50);   // Вставить элемент в начало контейнера.
    IntOne.show();
    IntOne.insertToEnd(604);        // Вставить элемент в конец контейнера.
    IntOne.show();
    IntOne.remove(0);               // Удалить элемент из контейнера.
    IntOne.show();
    IntOne.resize(5);               // Изменить размер контейнера.

    return 0;
}