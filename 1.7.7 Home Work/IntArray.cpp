#include "IntArray.h"

IntArray::IntArray() 
{
	std::cout << "����������� �� ��������� - " << this << std::endl;
}

IntArray::IntArray(int length) : _length(length) 
{
	if (length <= 0 || length > std::numeric_limits<int>::max())
	{
		throw BadLength();
	}

	try
	{
		_data = new int[length] {0};
	}
	catch (const std::exception& ex) 
	{
		std::cerr << "�� ������ �������� ������ " << ex.what() << std::endl;
		throw;
	}
	std::cout << "����������� �������� - " << this << std::endl;
}

IntArray::IntArray(const IntArray& other) 
{
// ���������� ������������ ���������, ������������ ����� �������, � ������ ������ � ����� ��������� �������� �����������.
	reallocate(other.getLength());

// �������� ��������, ����� _length ��� �����
	for (int i = 0; i < _length; ++i)
	{
		_data[i] = other._data[i];
	}
}

IntArray::IntArray(const std::initializer_list<int>& l) 
{
	_length = l.size();

	try 
	{
		_data = new int[_length] {0};
	}
	catch (const std::exception& ex) 
	{
		std::cerr << "�� ������ �������� ������ " << ex.what() << std::endl;
		throw;
	}

	int i = 0;
	for (const int* ptr = l.begin(); ptr != l.end() && i < _length; ++ptr, ++i) 
	{
		_data[i] = *ptr;
	}

	std::cout << "����������� initializer_list  - " << this << std::endl;
}


IntArray& IntArray::operator=(const IntArray& other) 
{
//��������, �� ��������� �� ������ ������ �� ����
	if (&other == this) return *this;

//���������� ������ ��������� � ������ �������� �����������
	reallocate(other.getLength());

//����� _length ��� ����� ����� ����� ������� ������� ����������� � ������� reallocate
	for (int i = 0; i < _length; ++i) {
		_data[i] = other._data[i];
	}

	return *this;
}

IntArray::~IntArray() 
{
	delete[] _data;

//��� �� ����� ������������� m_data � null ��� m_length � 0, ��� ��� ������ ��� ����� ����� ��������� ����� ����� ���� �������
	std::cout << "���������� �������� - " << this << std::endl << std::endl;
}

void IntArray::erase() 
{
	delete[] _data;

// ��� ����� ���������, ��� ����� �� ���������� ��� m_data �������� nullptr, �����
// �������� ��������� �� ������������� ������!
	_data = nullptr;
	_length = 0;
}

int& IntArray::operator[](int index) 
{
	if (index < 0 || index > _length) throw BadRange();
	return _data[index];
}

int IntArray::getLength() const 
{
	return _length;
}

// �������� ������ �������. ��� ������������ �������� ����� ����������. ��� ������� �������� ������.
void IntArray::reallocate(int newLength) 
{
// ������� �� ������� ��� ������������ ��������
	erase();

// ���� ��� ������ ������ ����� ������, �������� ����
	if (newLength <= 0 || newLength > std::numeric_limits<int>::max()) 
	{
		throw BadLength();
	}

	try 
	{
		_data = new int[newLength] {0};
	}
	catch (const std::exception& ex) 
	{
		std::cerr << "�� ������ �������� ������ " << ex.what() << std::endl;
		throw;
	}

	_length = newLength;
}

// resize �������� ������ �������. ��� ������������ �������� ����� ���������. ��� ������� �������� ��������.
void IntArray::resize(int newLength) 
{
// ���� ������ ��� ����� ������ �����, return
	if (newLength == _length)
		return;

// ���� �� �������� ������ �� ������� �������, ������ ��� � return
	if (newLength < 0 || newLength > std::numeric_limits<int>::max()) 
	{
		throw BadLength();
	}
	if (newLength == 0) 
	{
		erase();
		return;
	}

// ������ �� ����� ������������, ��� newLength �������� ��� ������� 1 �������. ���� ��������
// �������� ��������� �������: ������� �� �������� ����� ������. ����� ��
// ����� ���������� �������� �� ������������� ������� � ����� ������.
// ��� ������ ��� ����� �������, �� ����� ���������� ������ ������ � ������� m_data
// ��������� �� ����� ������.

// ������� �� ������ �������� ����� ������
	try 
	{
		int* newdata = new int[newLength] {0};  // int* data{ new int[newLength] }; - universal initialisation  

// ����� �� ������ ��������, ������� ��������� ���������� �� �������������
// ������� � ����� ������. �� ����� ����������� ������� ���������, ������� ����
// � ������� �� ���� ��������.
		if (_length > 0) 
		{

			int countNewElems = (newLength > _length) ? _length : newLength;

// ������ �������� �������� ���� �� ������
			for (int i = 0; i < countNewElems; ++i) 
			{
				newdata[i] = _data[i];
			}
		}

// ������ �� ����� ������� ������ ������, ������ ��� �� ��� ������ �� �����
		delete[] _data;

// � ������ ����� ����������� ����� ������! �������� ��������, ��� ��� ������ ������ ����� m_data
// �� ���� �� ������, ��� � ����� ����������� ���������� ������. ������ ���
// ������ ���� ��������� �����������, ��� �� ����� ����������, ����� ������ �� ������� ������� ���������.
		_data = newdata;
		_length = newLength;

	}
	catch (const std::exception& ex) 
	{
		std::cerr << "�� ������ �������� ������ " << ex.what() << std::endl;
		throw;
	}
}

void IntArray::insertBefore(int value, int index)
{
//�������� �� ������������ �������
	if (index < 0 || index > _length) throw BadRange();

// ������� ������� ����� ������ �� ���� ������� ������, ��� ������ ������
	try 
	{
		int* newdata = new int[_length + 1] {0};

// �������� ��� �������� �� �������
		for (int i = 0; i < index; ++i) 
		{
			newdata[i] = _data[i];
		}

// ��������� ��� ����� ������� � ����� ������
		newdata[index] = value;

// �������� ��� �������� ����� ������������ ��������
		for (int i = index; i < _length; ++i) 
		{
			newdata[i + 1] = _data[i];
		}

//�������, ������� ������ ������ � ���������� ������ ���� ����� ������
		delete[] _data;
		_data = newdata;
		++_length;
	}
	catch (const std::exception& ex) 
	{
		std::cerr << "�� ������ �������� ������ " << ex.what() << std::endl;
		throw; 
	}

}

void IntArray::insertToBeginning(int value)
{
	insertBefore(value, 0);
}

void IntArray::insertToEnd(int value)
{
	insertBefore(value, _length);
}

//������� ������� �� �������
void IntArray::remove(int index) 
{
// ��������� ������ �� ������ � ���������
	if (index < 0 || index > _length) throw BadRange();

// ���� ��� ��������� ���������� ������� � �������, ������� ������ ������ � ����� �� ����
	if (_length == 1) 
	{
		erase();
		return;
	}

	try 
	{
// ������� ������� ����� ������ �� ���� ������� ������, ��� ������ ������
		int* newdata = new int[_length - 1] {0};

// �������� ��� �������� �� �������
		for (int i = 0; i < index; ++i) 
		{
			newdata[i] = _data[i];
		}

// �������� ��� �������� ����� ���������� ��������
		for (int i = index + 1; i < _length; ++i) 
		{
			newdata[i - 1] = _data[i];
		}

// �������, ������� ������ ������ � ���������� ������ ���� ����� ������
		delete[] _data;
		_data = newdata;
		--_length;

	}
	catch (const std::exception& ex) 
	{
		std::cerr << "�� ������ �������� ������ " << ex.what() << std::endl;
		throw;
	}
}

void IntArray::show() const 
{
	for (int i = 0; i < _length; ++i) 
	{
		std::cout << _data[i];
		if (i != _length - 1) std::cout << ", ";
	}

	std::cout << std::endl;
}

bool IntArray::find(int value, size_t& index_result) 
{
	for (int i = 0; i < _length; ++i) 
	{
		if (_data[i] == value) 
		{
			index_result = i;
			return true;
		}
	}
	return false;
}