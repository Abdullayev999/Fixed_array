#include <iostream>
#include <stdexcept>

/*Задание 1:
	+ Реализуйте 2 класса исключений: LimitException, OutOfRangeException
	+ Реализуйте класс FixedArray<T, size_t> где T это тип элементов,
	которые хранятся в FixedArray а size_t их количество
	+ Реализуйте метод push_back для добавления элемента в конец массива.
	  Данный метод должен бросать исключение типа LimitException
	  если в массиве больше нет места
	+ Реализуйте operator[] для обращения по индексу к добавленным элементам
	  через push_back. Данный оператор должен бросать исключение типа
	  OutOfRangeException если вы вышли за пределы массива
	+ Реализуйте возможность внутри одного catch поймать как исключение
	  вида LimitException так и исключение вида OutOfRangeException*/



class Exception
{
public:
	const char* what() {
		return m_reason;
	}

	Exception(const char* reason)
	{
		m_reason = reason;
	}

	const char* m_reason;
};

class OutOfRangeException : public Exception
{
public:
	OutOfRangeException(const char* reason) :Exception(reason)
	{
		m_reason = reason;
	}
};

class LimitException :public Exception
{
public:
	LimitException(const char* reason) :Exception(reason)
	{
		m_reason = reason;
	}
};

template<typename T, size_t size>
class FixedArray
{
public:
	FixedArray()
	{
		m_data = new T[size];
	}

	void push_back(const T& element)
	{
		if (m_index < size)
		{
			m_data[m_index++] = element;
		}
		else
		{
			throw LimitException("Limit of size");
		}
	}

	T& operator[](const int element)
	{
		for (int i = 0; i < size; ++i)
		{
			if (m_data[i] == element)
			{
				return m_data[element];
			}
		}

		throw OutOfRangeException("Out of range");

	}

	~FixedArray()
	{
		delete[] m_data;
	}

private:

	friend std::ostream& operator<<(std::ostream& os, FixedArray& n)
	{
		if (n.m_index)
		{
			for (int i = 0; i < n.m_index; ++i)
				os << n[i] << ' ';
		}
		else
		{
			std::cout << "Not data";
		}
		return os;
	}
	size_t m_index = 0;
	T* m_data = nullptr;
};

enum { INDEX_HANDLING = 1, PUSH_BACK, PRINT_ARRAY };

int main()
{

	FixedArray<int, 3> fixed_arr;
	int action;
	std::cout << "Begin\n";
	int index = 0;
	try
	{
		while (true)
		{
			std::cout << "\n 1 - Index handling\n";
			std::cout << " 2 - Push_back\n";
			std::cout << " 3 - Print array\n\n";

			std::cin >> action;

			if (action == INDEX_HANDLING)
			{
				std::cout << "Enter number for Index handling\n";
				std::cin >> action;
				std::cout << "\na[index] = " << fixed_arr[action] << '\n';
			}
			else if (action == PUSH_BACK)
			{
				std::cout << "Enter number for push_back\n";
				std::cin >> action;
				std::cout << "\na.push_back( " << index++ << " ) = " << action;
				fixed_arr.push_back(action);
				std::cout << '\n';
			}
			else if (action == PRINT_ARRAY)
			{
				std::cout << "\nPrint array = " << fixed_arr << '\n';
			}
		}
	}
	catch (Exception& ex)
	{
		std::cout << "\n << " << ex.what() << " >>\n";
	}
	std::cout << "\nEnd\n";
}
