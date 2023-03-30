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
    IntOne.insertToEnd(1604);        // �������� ������� � ����� ����������.
    IntOne.show();
    IntOne.remove(0);               // ������� ������� �� ����������.
    IntOne.show();
    IntOne.resize(5);               // �������� ������ ����������.

    Array<int> intArray(10);
    Array<double> doubleArray(10);

    for (int count = 0; count < intArray.getLength(); ++count)
    {
        intArray[count] = count;
        doubleArray[count] = count + 0.5;
    }

    for (int count = intArray.getLength() - 1; count >= 0; --count)
        std::cout << intArray[count] << "\t" << doubleArray[count] << '\n';

    return 0;
}