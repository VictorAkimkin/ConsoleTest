#pragma once
#ifndef simplearray_H_
#define simplearray_H_

#include <iostream>

template <class T>
class simplearray
{

public:
	explicit simplearray(int size);
	explicit simplearray(std::initializer_list <T> L);
	simplearray(const simplearray <T>& other);
	simplearray(simplearray <T>&& other);
	~simplearray();

	void clear();
	void delete_arr();
	int getSize() const;

	// операторы
	T& operator [] (const int i)const;

	simplearray <T> operator+ (const simplearray <T>& other);
	simplearray <T>& operator= (const simplearray <T>& other);
	simplearray <T>& operator= (const std::initializer_list <T> L);

	template <class U> // class U вместо class T. иначе не будет рабоать
	friend std::ostream& operator<< (std::ostream&, const simplearray <U>&);

private:
	void initialize_by_initializer(const std::initializer_list <T>& L);

private:
	T* arr;
	int size;
};

// ******************************************************************
// ОПРЕДЕЛЕНИЯ МЕТОДОВ ШАБЛОННОГО КЛАССА МОЖНО ДЕЛАТЬ ТОЛЬКО В ХЭДЕРЕ 
// (либо подключать в main cpp-файл вместо h-файла, что выбивается из общего правила)
// конструкторы и деструктор

template<class T>
simplearray<T> ::simplearray(int size) :arr(new T[size]), size(size)
{
	clear();
}

template<class T>
simplearray<T>::simplearray(std::initializer_list<T> L)
{
	initialize_by_initializer(L);
}

template<class T>
simplearray<T>::simplearray(const simplearray <T>& other)
{
	size = other.getSize();
	arr = new T[size];
	memcpy(arr, other.arr, sizeof(T) * size);
}


template<class T>
simplearray<T>::simplearray(simplearray<T>&& other)
{
	size = other.getSize();
	arr = other.arr;
	other.arr = nullptr;
}

// методы
template<class T>
simplearray<T>::~simplearray()
{
	delete_arr();
}

template<class T>
void simplearray<T>::clear()
{
	memset(arr, 0, sizeof(T) * size);
}

template<class T>
void simplearray<T>::delete_arr()
{
	if (arr)
	{
		delete[] arr;
		arr = nullptr;
		size = 0;
	}
}

template<class T>
int simplearray<T>::getSize() const
{
	return this->size;
}

// перегрузка операторов
template<class T>
T& simplearray<T>::operator[](const int i)const
{
	return arr[i];
}

template<class T>
simplearray<T> simplearray<T>::operator+(const simplearray<T>& other)
{
	simplearray <T> new_simplearray(size + other.getSize());
	memcpy(new_simplearray.arr, arr, size * sizeof(T));
	memcpy(new_simplearray.arr + size, other.arr, other.getSize() * sizeof(T));
	return new_simplearray;
}

template<class T>
simplearray<T>& simplearray<T>::operator=(const simplearray<T>& other)
{
	delete_arr();
	size = other.getSize();
	arr = new T[size];
	memcpy(arr, other.arr, size * sizeof(T));
	return *this;
}

template<class T>
simplearray<T>& simplearray<T>::operator=(const std::initializer_list <T> L)
{
	delete_arr();
	initialize_by_initializer(L);
	return *this;
}

template<class T>
void simplearray<T>::initialize_by_initializer(const std::initializer_list<T>& L)
{
	size = L.size(); arr = new T[size];
	int i = 0;
	for (auto& elem : L) arr[i++] = elem;
}

#endif

// перегрузка ostream
template<class T>
std::ostream& operator<< (std::ostream& out, const simplearray <T>& sa)
{
	int i = 0;
	int max = sa.getSize();
	for (i; i < max; ++i)
	{
		out << sa.arr[i] << " ";
		if ((i % 2)) out << "\n";
	}
	if ((i % 2)) out << "\n";
	return out;
}
