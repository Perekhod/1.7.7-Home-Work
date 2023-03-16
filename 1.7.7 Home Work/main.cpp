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

    IntArray IntOne(10);            // ������� ���������.
    IntOne.show();
    IntOne.insertBefore(10, 5);     // �������� ������� � ���������.
    IntOne.show();
    IntOne.insertToBeginning(50);   // �������� ������� � ������ ����������.
    IntOne.show();
    IntOne.insertToEnd(604);        // �������� ������� � ����� ����������.
    IntOne.show();
    IntOne.remove(0);               // ������� ������� �� ����������.
    IntOne.show();
    IntOne.resize(5);               // �������� ������ ����������.

    return 0;
}