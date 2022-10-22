#pragma once
#include <iostream>

using std::cout;
using std::endl;


template <class T>// перегрузка ostream << для vector
std::ostream& operator<<(std::ostream& out, std::vector<T>& vec)
{
	for (auto& elem : vec) out << elem << "  ";
	if (!vec.empty())out << std::endl;
	return out;
}
struct TestMemoryAllocationClass // класс для тестирования выделения памяти
{
	TestMemoryAllocationClass() { std::cout << "Constructor TestMemoryAllocationClass #" << ++counter << "\n"; }
	~TestMemoryAllocationClass() { std::cout << "Destructor  TestMemoryAllocationClass #" << counter-- << "\n"; }
	static size_t GetCounter() { return counter; }
private:
	static size_t counter;
};

