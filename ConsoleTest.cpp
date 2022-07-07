// ConsoleTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma once
#include <iostream>
#include <tuple>
#include <cassert>
#include <functional>
#include <algorithm>

#include "MyMath.h"
#include "simplearray.h"
#include "HashTable.h"
#include "VariadicTemplate.h"
int global1;
double  global2;
extern int ei;
int ei{};

void initionalizer();
void rhombshaped_heritage();
void operators_redefinition();
void hashTable();
void variadic_template();
void memory_allocation1();
void memory_allocation2();
struct A // класс для тестирования выделения памяти
{
	A() { std::cout << "Constructor A #" << ++counter << "\n"; }
	~A() { std::cout << "Destructor  A #" << counter-- << "\n"; }
	static size_t GetCounter() {return counter;}
	private:
	static size_t counter;
};
size_t A::counter; // инициализация статического поля класса
void swaping();
void remove_sort();

template <class T>// перегрузка ostream << для vector
std::ostream& operator<<(std::ostream& out, std::vector<T>& vec)
{
	for (auto &elem:vec) out << elem << "  ";
	if (!vec.empty())out << std::endl;
	return out;
}

int main()
{
	setlocale(LC_ALL, "Rus");

	////
	//// инициализация, виды инициализации нулем
	// initionalizer();
	//std::cout << "initionalizer() end\n\n";
	////
	//// ромбовидное наследование: класс наследник от двух классов с общим предком
	//rhombshaped_heritage();
	//std::cout << "rhombshaped_heritage() end \n\n";
	//// 
	//// перегрузка операторов шаблонного класса с динамическим массивом и перегрузка ostream
	//operators_redefinition();
	//std::cout << "operators_redefinition() end\n\n";
	//// 
	//// хэш таблица 
	//hashTable();
	//   std::cout << "hashTable() end\n\n";
	//// 
	//// вариативные шаблоны и кортежи
	//variadic_template();
	//std::cout << "variadic_template() end\n\n";
	//// 
	//// выделение и очищение памяти используя malloc realloc free new delete (два варианта работы)
	//memory_allocation1();  
	//memory_allocation2();
	//std::cout << "memory_allocation() end\n\n";
	//// варианты смены значений переменных
	// swaping();
	// std::cout << "swaping() end\n\n";
	//// 
	//// сортировка и удаление элементов контейнера
	// remove_sort();
	// std::cout << "remove_sort() end\n\n";
	

	std::cout << "\n\n"; system("pause");
}

void initionalizer() 
{
	struct st { int a; float b; char c; };
	union un { int a; double b; char c; };
	un u1; u1.a = 0;
	un u2; u2.b = 0;
	un u3; u3.c = 0;
	st s1;// не инициализируется
	// поля инициализируются нулями, там где не указано другое значение
	st s2{};
	st s3 = {};
	st s4 = st();
	st s5(5, '5');
	st s6{ .b = 6.0 };//c++20
	static int si;

	thread_local double tld;
	char ch[5] = "1";
	int intmas[5] = { 1,2 };
	std::string str; str.resize(5);
	// ----------------------------------------------------------------
	void (*fu)(un&, int) = [](un& u, int num) {std::cout << "  u" << num << ":  a= " << u.a << "  b= " << u.b << "  c= " << u.c << " \n"; };
	fu(u1, 1); fu(u2, 2); fu(u3, 3);
	auto f = [](st& s, int num) {std::cout << "  s" << num << ":  a= " << s.a << "  b= " << s.b << "  c= " << s.c << " \n"; };
	f(s1, 1); f(s2, 2); f(s3, 3); f(s4, 4); f(s5, 5); f(s6, 6);
	std::cout << "  global1 : " << global1 << " \n";
	std::cout << "  global2 : " << global2 << " \n";
	std::cout << "  static int si : " << si << " \n";
	std::cout << "  extern int ei : " << ei << " \n";
	std::cout << "  thread_local double tld : " << si << " \n";
	for (int i{}; i < sizeof(ch); ++i)
		std::cout << "  ch[" << i << "] = " << ch[i] << " \n";
	for (int i{}; i < sizeof(intmas) / sizeof(int); ++i)
		std::cout << "  intmas[" << i << "] = " << intmas[i] << " \n";

	for (int i{}; i < str.size(); ++i)
		std::cout << "  str[" << i << "] = " << str[i] << " \n";
}
void rhombshaped_heritage()
{
	Calc a;
	Sum a1;
	Sum a2(2, 3);
	Multiply b1;
	Multiply b2(5, 3);
	MyMath c1;
	MyMath c2(4, 5);
	
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "Sum a1; a1.Result()= " << a1.Result(); std::cout << "\t\t";
	std::cout << "Sum a2(2,3); a2.Result()= " << a2.Result();
	std::cout << "\n";
	std::cout << "Multiply b1; b1.Result()= " << b1.Result(); std::cout << "\t\t";
	std::cout << "Multiply b2(5,3); b2.Result()= " << b2.Result();
	std::cout << "\n";
	std::cout << "\n";
	
	std::cout << "MyMath c1; c1.sumXY()= " << c1.sumXY(); std::cout << "\t\t";
	std::cout << "MyMath c1; c1.multiplyXY()= " << c1.multiplyXY();
	std::cout << "\n";
	std::cout << "MyMath c2(4,5); c2.multiplyXY()= " << c2.multiplyXY(); std::cout << "\t\t";
	std::cout << "MyMath c2(4,5); c2.sumXY()= " << c2.sumXY();
	std::cout << "\n";
}
void operators_redefinition()
{
	simplearray  <int> a(2);
	a[0] = 12; a[1] = 14;
	std::cout << "a =\n" << a;
	std::cout << "\n";

	simplearray <int> b(4);
	b[0] = 23; b[1] = 26; b[2] = 29; b[3] = 22;
	std::cout << "b =\n" << b;
	std::cout << "\n";

	simplearray <int> c(a);
	std::cout << "c(a) =\n" << c;
	std::cout << "\n";

	simplearray <int> d({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	std::cout << "d({ 1, 2, 3, 4, 5, 6, 7, 8, 9 } =\n" << d;
	std::cout << "\n";
	d = a;
	std::cout << "d = a =\n" << d;
	std::cout << "\n";
	d = { 30,31,32 };
	std::cout << "d = {0,1,2} =\n" << d;
	std::cout << "\n";

	simplearray <int> e(a + b);
	std::cout << "e(a + b) =\n" << e;
	std::cout << "\n";

	c = (d + b);
	std::cout << "c= (d + b) =\n" << c;
	std::cout << "\n";

	c = {5};
	std::cout << "c={5} =\n" << c;
	std::cout << "\n";
}
void hashTable()
{
	HashTable ht(4);
	auto data = {
		std::make_pair("Коля Петров", "пекарь"),
		std::make_pair("Оля Петрова", "актрисса"),
		std::make_pair("Саша Петров", "пекарь"),
		std::make_pair("Василий Конюхов", "менеджер"),
		std::make_pair("Николай Рыбин", "грузчик"),
		std::make_pair("Надежда Комарова", "водитель"),
		std::make_pair("Василий Конюхов", "менеджер по продажам")
	};


	for (auto& elem : data)
		if (!ht.addnew(elem.first, elem.second))
			std::cout << ht.report() << "\n";

	std::cout << "\n";
	ht.print_table();
	std::cout << "\n";

	ht.erase("Саша Петров"); std::cout << ht.report() << "\n";
	ht.erase("Саша Петров"); std::cout << ht.report() << "\n";

	std::cout << "\n";
	ht.print_table();
	std::cout << "\n";
}
void variadic_template()
{
	auto arg1 = 'b';
	auto arg2 = 2;
	auto arg3 = 2.5;
	auto arg4 = "std::tie";

	auto ti = std::tie(arg1, arg2, arg3, arg4);
	print_tuple(ti);
	std::cout << '\n';

	auto t = std::make_tuple('a', 1, 1.5, "std::make_tuple. many arguments");
	print_tuple(t);
	std::cout << '\n';

	auto t2 = std::make_tuple("std::make_tuple. one argument");
	print_tuple(t2);
	std::cout << '\n';

	auto t3 = std::make_tuple();
	print_tuple(t3);
	std::cout << '\n';

	//std::apply([](auto &&... args) { my_func(args...); }, my_tuple);
	auto arg5 = "variadic&. many arguments ";
	print_tuple(arg1, arg2, arg3, arg5);
	std::cout << '\n';
	print_tuple('c', 3, 3.5, "variadic&&. many arguments");
	std::cout << '\n';
	print_tuple("variadic&&. one argument");
	std::cout << '\n';
	auto the_arg = "variadic&. one argument";
	print_tuple(the_arg);
	std::cout << '\n';
}
void memory_allocation1()
{
	A* massA = (A*)malloc(sizeof(A));
	assert(("malloc Error", massA));
	new (massA) A;
	std::function<void(int)> destructor = [&](int index) // объявляем как std::function для возможности рекурсии
	{
		if (!A::GetCounter() || index >= A::GetCounter()) return;
		for (int i = A::GetCounter() - 1; i >= index; --i)
			(massA + i)->~A();
		if (index)
		{
			A* tmpptr = (A*)realloc(massA, sizeof(A) * index);
			if (!tmpptr) { destructor(0); exit(1); }
			massA = tmpptr;
		}
		else free(massA);
	};
	for (int i = 3; i; --i)
	{
		int size;
		do
		{
			std::cout << "Текущий размер массива объектов А = " << A::GetCounter() << ".\n          Введите новый размер (от 1 до 5) массива объектов  А\n";
			std::cin >> size;
			if (!std::cin.good()) // защита от некорректного ввода
			{
				std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (size < 1 || size > 5);
		if (size > A::GetCounter())
		{
			A* tmpptr = (A*)realloc(massA, sizeof(A) * size);
			if (!tmpptr) { destructor(0); exit(1); }
			massA = tmpptr;
			for (int j = A::GetCounter(); j < size; ++j) new (massA + j) A;
		}
		else
		{
			if (size < A::GetCounter())
			{
				destructor(size);
			}
			else std::cout << "Новый размер массива объектов А равен текущему размеру. Перераспределение памяти не произведено\n\n";
		}
	}
	std::cout << "\nОчищаем память\n";
	destructor(0);
	std::cout << '\n';
}
void memory_allocation2()
{
	const int subMassSize = 5;
	A** massA = (A**)malloc(sizeof(A*));
	assert(("malloc Error", massA));
	massA[0] = new A[subMassSize];
	std::function<void(int)> destructor = [&](int index) // объявляем как std::function для возможности рекурсии
	{
		int mass_counter = A::GetCounter() / subMassSize;
		if (!mass_counter || index >= mass_counter) return;
		for (int i = mass_counter; i > index; --i)
			delete[] massA[i - 1];
		if (index)
		{
			A** tmpptr = (A**)realloc(massA, sizeof(A*) * index);
			if (!tmpptr) { destructor(0); exit(1); }
			massA = tmpptr;
		}
		else free(massA);
	};
	for (int i = 3; i; --i)
	{
		int mass_counter = A::GetCounter() / subMassSize;
		int size;
		do 
		{
			std::cout << "Текущий размер массива массивов объектов А = " << mass_counter
				<<"\nОбщее количество объектов = " << A::GetCounter()
				<< ".\n          Введите новый размер (от 1 до 5) массива массивов объектов  А\n";
			std::cin >> size;
			if (!std::cin.good()) // защита от некорректного ввода
			{
				std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (size < 1 || size > 5);
		if (size > mass_counter)
		{
			A** tmpptr = (A**)realloc(massA, sizeof(A*) * size);
			if (!tmpptr) { destructor(0); exit(1); }
			massA = tmpptr;
			for (int j = mass_counter; j < size; ++j)	massA[j] = new A[subMassSize];
		}
		else
		{
			if (size < mass_counter)
			{
				destructor(size);
			}
			else std::cout << "Новый размер массива объектов А равен текущему размеру. Перераспределение памяти не произведено\n\n";
		}
	}
	std::cout << "\nОчищаем память\n";
	destructor(0);
	std::cout << '\n';
}
void swaping()
{
	float a = 2.2, b = 3.3;
	std::cout << "a = " << a << "       b = " << b << "\n";
	std::swap(a, b); //1
	std::cout << "a = " << a << "       b = " << b << "\n";
	a += b; b = a - b; a -= b; //2
	std::cout << "a = " << a << "       b = " << b << "\n";
	std::tie(a, b) = std::make_tuple(b, a); //3
	std::cout << "a = " << a << "       b = " << b << "\n";
	decltype (a) tmp = std::move(a);//4
	a = std::move(b);
	b = std::move(tmp);
	std::cout << "a = " << a << "       b = " << b << "\n";
}
void remove_sort()
{
	std::vector <int> v = { 35,46,4,1,32,43,5,24,34 };
	std::cout << " original___________________\n" << v; // ostream << перегружен для vector
	std::qsort(v.data(), v.size(), sizeof(int), [](const void* it1, const void* it2) {
		if ((*static_cast<const int*>(it1)) < (*static_cast<const int*>(it2))) return -1;
		return static_cast<int> ((*static_cast<const int*>(it1)) > (*static_cast<const int*>(it2))); });
	std::cout << "std::qsort < ______________ \n" << v;
	std::qsort(v.data(), v.size(), sizeof(int), [](const void* it1, const void* it2) {
		auto res = (*static_cast<const int*>(it1)) <=> (*static_cast<const int*>(it2));
		if (res > 0) return -1;
		return static_cast<int> (res < 0); });
	std::cout << "std::qsort > _______________\n" << v;
	// #include <algorithm>
	std::sort(v.begin(), v.end());
	std::cout << "std::sort___________________\n" << v;
	std::sort(v.begin(), v.end(), std::greater<>());
	std::cout << "std::sort std::greater<>()__\n" << v;
	std::sort(v.begin(), v.end(), std::less<>());
	std::cout << "std::sort std::less<>()_____\n" << v;
	std::cout << "\n\n";
	std::vector <int> v2 = { 35,46,4,1,32,43,5,24,34 };
	std::cout << " original___________________\n" << v2; // ostream << перегружен для vector
	auto it = std::remove_if(v2.begin(), v2.end(), [](int elem) {return (elem > 24 && elem < 45); });
	v2.erase(it, v2.end());
	std::cout << "std::remove_if___24> x <45___\n" << v2;
	it = std::remove(v2.begin(), v2.end(), 24); v2.erase(it, v2.end());
	v2.erase(std::remove(v2.begin(), v2.end(), 46), v2.end());
	std::cout << "std::remove________24,46____\n" << v2;
}