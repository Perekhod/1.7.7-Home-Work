#include "IntArray.h"

IntArray::IntArray() 
{
	std::cout << "Конструктор по умолчанию - " << this << std::endl;
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
		std::cerr << "Не смогли выделить память " << ex.what() << std::endl;
		throw;
	}
	std::cout << "Конструктор сработал - " << this << std::endl;
}

IntArray::IntArray(const IntArray& other) 
{
// Уничтожаем существующий контейнер, реаллоцируем новый нулевой, с нужной длиной и далее совершаем глубокое копирование.
	reallocate(other.getLength());

// Копируем элементы, здесь _length уже новая
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
		std::cerr << "Не смогли выделить память " << ex.what() << std::endl;
		throw;
	}

	int i = 0;
	for (const int* ptr = l.begin(); ptr != l.end() && i < _length; ++ptr, ++i) 
	{
		_data[i] = *ptr;
	}

	std::cout << "Конструктор initializer_list  - " << this << std::endl;
}


IntArray& IntArray::operator=(const IntArray& other) 
{
//Проверка, не ссылается ли другой объект на себя
	if (&other == this) return *this;

//Уничтожаем старый контейнер и делаем глубокое копирование
	reallocate(other.getLength());

//Здесь _length уже имеет новую длину другого объекта назначенную в функции reallocate
	for (int i = 0; i < _length; ++i) {
		_data[i] = other._data[i];
	}

	return *this;
}

IntArray::~IntArray() 
{
	delete[] _data;

//Нам не нужно устанавливать m_data в null или m_length в 0, так как объект все равно будет уничтожен сразу после этой функции
	std::cout << "Деструктор сработал - " << this << std::endl << std::endl;
}

void IntArray::erase() 
{
	delete[] _data;

// Нам нужно убедиться, что здесь мы установили для m_data значение nullptr, иначе
// оставить указатель на освобожденную память!
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

// Изменяет размер массива. Все существующие элементы будут уничтожены. Эта функция работает быстро.
void IntArray::reallocate(int newLength) 
{
// Сначала мы удаляем все существующие элементы
	erase();

// Если наш массив сейчас будет пустым, вернемся сюда
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
		std::cerr << "Не смогли выделить память " << ex.what() << std::endl;
		throw;
	}

	_length = newLength;
}

// resize изменяет размер массива. Все существующие элементы будут сохранены. Эта функция работает медленно.
void IntArray::resize(int newLength) 
{
// если массив уже имеет нужную длину, return
	if (newLength == _length)
		return;

// Если мы изменяем размер до пустого массива, делаем это и return
	if (newLength < 0 || newLength > std::numeric_limits<int>::max()) 
	{
		throw BadLength();
	}
	if (newLength == 0) 
	{
		erase();
		return;
	}

// Теперь мы можем предположить, что newLength содержит как минимум 1 элемент. Этот алгоритм
// работает следующим образом: сначала мы выделяем новый массив. Тогда мы
// будем копировать элементы из существующего массива в новый массив.
// Как только это будет сделано, мы можем уничтожить старый массив и сделать m_data
// указываем на новый массив.

// Сначала мы должны выделить новый массив
	try 
	{
		int* newdata = new int[newLength] {0};  // int* data{ new int[newLength] }; - universal initialisation  

// Затем мы должны выяснить, сколько элементов копировать из существующего
// массива в новый массив. Мы хотим скопировать столько элементов, сколько есть
// в меньшем из двух массивов.
		if (_length > 0) 
		{

			int countNewElems = (newLength > _length) ? _length : newLength;

// Теперь копируем элементы один за другим
			for (int i = 0; i < countNewElems; ++i) 
			{
				newdata[i] = _data[i];
			}
		}

// Теперь мы можем удалить старый массив, потому что он нам больше не нужен
		delete[] _data;

// И вместо этого используйте новый массив! Обратите внимание, что это просто делает точку m_data
// по тому же адресу, что и новый динамически выделенный массив. Потому что
// данные были размещены динамически, они не будут уничтожены, когда выйдут за пределы области видимости.
		_data = newdata;
		_length = newLength;

	}
	catch (const std::exception& ex) 
	{
		std::cerr << "Не смогли выделить память " << ex.what() << std::endl;
		throw;
	}
}

void IntArray::insertBefore(int value, int index)
{
//Проверка на допустимость индекса
	if (index < 0 || index > _length) throw BadRange();

// Сначала создаем новый массив на один элемент больше, чем старый массив
	try 
	{
		int* newdata = new int[_length + 1] {0};

// Копируем все элементы до индекса
		for (int i = 0; i < index; ++i) 
		{
			newdata[i] = _data[i];
		}

// Вставляем наш новый элемент в новый массив
		newdata[index] = value;

// Копируем все значения после вставленного элемента
		for (int i = index; i < _length; ++i) 
		{
			newdata[i + 1] = _data[i];
		}

//Наконец, удаляем старый массив и используем вместо него новый массив
		delete[] _data;
		_data = newdata;
		++_length;
	}
	catch (const std::exception& ex) 
	{
		std::cerr << "Не смогли выделить память " << ex.what() << std::endl;
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

//Удаляет элемент из массива
void IntArray::remove(int index) 
{
// Проверяем входил ли индекс в имеющиеся
	if (index < 0 || index > _length) throw BadRange();

// Если это последний оставшийся элемент в массиве, сделать массив пустым и выйти из него
	if (_length == 1) 
	{
		erase();
		return;
	}

	try 
	{
// Сначала создаем новый массив на один элемент меньше, чем старый массив
		int* newdata = new int[_length - 1] {0};

// Копируем все элементы до индекса
		for (int i = 0; i < index; ++i) 
		{
			newdata[i] = _data[i];
		}

// Копируем все значения после удаленного элемента
		for (int i = index + 1; i < _length; ++i) 
		{
			newdata[i - 1] = _data[i];
		}

// Наконец, удаляем старый массив и используем вместо него новый массив
		delete[] _data;
		_data = newdata;
		--_length;

	}
	catch (const std::exception& ex) 
	{
		std::cerr << "Не смогли выделить память " << ex.what() << std::endl;
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