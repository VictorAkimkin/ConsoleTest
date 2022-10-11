﻿// ConsoleTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma once
#include <iostream>
#include <tuple>
#include <cassert>
#include <functional>
#include <algorithm>
#include <thread>
#include <queue>
#include <future>
#include <chrono>

#include "Header.h"
#include "MyMath.h"
#include "simplearray.h"
#include "HashTable.h"
#include "VariadicTemplate.h"
#include "mutex_demo.h"
#include "atomic_demo.h"
#include "futureAsync.h"
#include "OnTimer.h"
#include "Islands.h"
#include "MazeGuide.h"
#include "property.h"


using std::cout;
//typedef std::vector <int> VINT;
using  VINT = std::vector <int>;
int global1;
double  global2;
extern int ei;
int ei{};
size_t A::counter; // инициализация статического поля класса A (описан в  "Header.h")
thread_local int tli;

void initionalizer();
void thread_local_variable();
void rhombshaped_heritage();
void rhombshaped_heritage_callordering();
void operators_redefinition();
void hashTable();
void variadic_template();
void memory_allocation1();
void memory_allocation2();
void swaping();
void remove_sort();
void mutexLock();
void atomic();
void asyncTasks();
void timer();
void islands();
void mazeGuide();
void GetSetProperty();

int main()
{
	setlocale(LC_ALL, "Rus");
	////
	//// инициализация, виды инициализации нулем
	// initionalizer();
	// cout << "initionalizer() end\n\n";
	////
    //// thread_local поведение
	// thread_local_variable();
	 // cout << "thread_local_variable() end\n\n";
	 ////
	//// ромбовидное наследование: класс наследник от двух классов с общим предком
	//rhombshaped_heritage();
	//rhombshaped_heritage_callordering();//порядок вызова конструкторов/деструкторов и обязательность вирульаного деструктора
	// cout << "rhombshaped_heritage() end \n\n";
	//// 
	//// перегрузка операторов шаблонного класса с динамическим массивом и перегрузка ostream
	//operators_redefinition();
	// cout << "operators_redefinition() end\n\n";
	//// 
	//// хэш таблица 
	//hashTable();
	//   cout << "hashTable() end\n\n";
	////
	//// вариативные шаблоны и кортежи
	//variadic_template();
	// cout << "variadic_template() end\n\n";
	////
	//// выделение и очищение памяти используя malloc realloc free new delete (два варианта работы)
	//memory_allocation1();  
	//memory_allocation2();
	// cout << "memory_allocation() end\n\n";
	//// варианты смены значений переменных
	// swaping();
	//  cout << "swaping() end\n\n";
	////
	//// сортировка и удаление элементов контейнера
	//remove_sort();
	// cout << "remove_sort() end\n\n";
	////
	//// захват мьютекса
	//mutexLock();
	//cout << "mutexLock() end\n\n";
	//// 
	//// atomic переменные
	//atomic(); 
	//cout << "atomic() end\n\n";
	//// выполнение ассинхронных задач
	//asyncTasks();
	//cout << "asyncTasks() end\n\n";
	//// запуск функции асинхронно по таймеру.
	//timer();
	//cout << "timer() end\n\n";
	//// определение островков в массиве
	//islands();
	//cout << "islands() end\n\n";
	//// поиск выхода в лабиринте
	// mazeGuide();
	//cout << "islands() end\n\n";
	//// демонстрация property
	// GetSetProperty();
	//cout << "GetSetProperty() end\n\n";
        
	cout << "\n\n"; system("pause");
}
void initionalizer()
{
	struct st {int a; float b; char c; };
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
	char ch[5] = "12";
	int intmas[5] = { 3,4 };
	std::string str; str.resize(5);
	// ----------------------------------------------------------------
	void (*fu)(un&, int) = [](un& u, int num) {cout << "  u" << num << ":  a= " << u.a << "  b= " << u.b << "  c= " << u.c << " \n"; };
	fu(u1, 1); fu(u2, 2); fu(u3, 3);
	auto f = [](st& s, int num) {cout << "  s" << num << ":  a= " << s.a << "  b= " << s.b << "  c= " << s.c << " \n"; };
	f(s1, 1); f(s2, 2); f(s3, 3); f(s4, 4); f(s5, 5); f(s6, 6);
	cout << "  global1 : " << global1 << " \n";
	cout << "  global2 : " << global2 << " \n";
	cout << "  static int si : " << si << " \n";
	cout << "  extern int ei : " << ei << " \n";
	cout << "  thread_local double tld : " << si << " \n";
	for (int i{}; i < sizeof(ch); ++i)
		cout << "  ch[" << i << "] = " << ch[i] << " \n";
	for (int i{}; i < sizeof(intmas) / sizeof(int); ++i)
		cout << "  intmas[" << i << "] = " << intmas[i] << " \n";
	for (int i{}; i < str.size(); ++i)
		cout << "  str[" << i << "] = " << str[i] << " \n";
}
void thread_local_variable()
{
	auto f = [](int val) {tli = val; std::cout << tli; };
	tli = 100;
	std::thread t1(f, 1);
	std::thread t2(f, 2);
	std::thread t3(f, 3);

	t1.join();
	t2.join();
	t3.join();
	cout << " ";
	std::cout << tli << std::endl;
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

	cout << "\n\n";
	cout << "Sum a1; a1.Result()= " << a1.Result(); cout << "\t\t";
	cout << "Sum a2(2,3); a2.Result()= " << a2.Result();
	cout << "\n";
	cout << "Multiply b1; b1.Result()= " << b1.Result(); cout << "\t\t";
	cout << "Multiply b2(5,3); b2.Result()= " << b2.Result();
	cout << "\n\n";
	cout << "MyMath c1; c1.sumXY()= " << c1.sumXY(); cout << "\t\t";
	cout << "MyMath c1; c1.multiplyXY()= " << c1.multiplyXY();
	cout << "\n";
	cout << "MyMath c2(4,5); c2.multiplyXY()= " << c2.multiplyXY(); cout << "\t\t";
	cout << "MyMath c2(4,5); c2.sumXY()= " << c2.sumXY();
	cout << "\n";
}
void rhombshaped_heritage_callordering()
{
	// виртуальный деструктор базового класса обязателен при использоваии указателя на базывый класс хранящий объект потомка
	Calc *c1= new MyMath(2, 3);       std::cout << "\n\n\n";
	delete c1; 
}
void operators_redefinition()
{
	simplearray  <int> a(2);
	a[0] = 12; a[1] = 14;
	cout << "a =\n" << a;
	cout << "\n";

	simplearray <int> b(4);
	b[0] = 23; b[1] = 26; b[2] = 29; b[3] = 22;
	cout << "b =\n" << b;
	cout << "\n";

	simplearray <int> c(a);
	cout << "c(a) =\n" << c;
	cout << "\n";

	simplearray <int> d({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	cout << "d({ 1, 2, 3, 4, 5, 6, 7, 8, 9 } =\n" << d;
	cout << "\n";
	d = a;
	cout << "d = a =\n" << d;
	cout << "\n";
	d = { 30,31,32 };
	cout << "d = {0,1,2} =\n" << d;
	cout << "\n";

	simplearray <int> e(a + b);
	cout << "e(a + b) =\n" << e;
	cout << "\n";

	c = (d + b);
	cout << "c= (d + b) =\n" << c;
	cout << "\n";

	c = { 5 };
	cout << "c={5} =\n" << c;
	cout << "\n";
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
			cout << ht.report() << "\n";

	cout << "\n";
	ht.print_table();
	cout << "\n";

	ht.erase("Саша Петров"); cout << ht.report() << "\n";
	ht.erase("Саша Петров"); cout << ht.report() << "\n";

	cout << "\n";
	ht.print_table();
	cout << "\n";
}
void variadic_template()
{
	auto arg1 = 'b';
	auto arg2 = 2;
	auto arg3 = 2.5;
	auto arg4 = "std::tie";

	auto ti = std::tie(arg1, arg2, arg3, arg4);
	print_tuple(ti);
	cout << '\n';

	auto t = std::make_tuple('a', 1, 1.5, "std::make_tuple. many arguments");
	print_tuple(t);
	cout << '\n';

	auto t2 = std::make_tuple("std::make_tuple. one argument");
	print_tuple(t2);
	cout << '\n';

	auto t3 = std::make_tuple();
	print_tuple(t3);
	cout << '\n';

	//std::apply([](auto &&... args) { my_func(args...); }, my_tuple);
	auto arg5 = "variadic&. many arguments ";
	print_tuple(arg1, arg2, arg3, arg5);
	cout << '\n';
	print_tuple('c', 3, 3.5, "variadic&&. many arguments");
	cout << '\n';
	print_tuple("variadic&&. one argument");
	cout << '\n';
	auto the_arg = "variadic&. one argument";
	print_tuple(the_arg);
	cout << '\n';
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
			cout << "Текущий размер массива объектов А = " << A::GetCounter() << ".\n          Введите новый размер (от 1 до 5) массива объектов  А\n";
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
			else cout << "Новый размер массива объектов А равен текущему размеру. Перераспределение памяти не произведено\n\n";
		}
	}
	cout << "\nОчищаем память\n";
	destructor(0);
	cout << '\n';
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
			cout << "Текущий размер массива массивов объектов А = " << mass_counter
				<< "\nОбщее количество объектов = " << A::GetCounter()
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
			else  cout << "Новый размер массива объектов А равен текущему размеру. Перераспределение памяти не произведено\n\n";
		}
	}
	cout << "\nОчищаем память\n";
	destructor(0);
	cout << '\n';
}
void swaping()
{
	float a = 2.2, b = 3.3;
	cout << "a = " << a << "       b = " << b << "\n";
	std::swap(a, b); //1
	cout << "a = " << a << "       b = " << b << "\n";
	a += b; b = a - b; a -= b; //2
	cout << "a = " << a << "       b = " << b << "\n";
	std::tie(a, b) = std::make_tuple(b, a); //3
	cout << "a = " << a << "       b = " << b << "\n";
	decltype (a) tmp = std::move(a);//4
	a = std::move(b);
	b = std::move(tmp);
	cout << "a = " << a << "       b = " << b << "\n";
}
void remove_sort()
{
	VINT v = { 35,46,4,1,32,43,5,24,34 };
	VINT v2(v);
	cout << " original___________________\n" << v; // ostream << перегружен для vector
	auto reverse = [](std::vector<int>::iterator it_begin, std::vector<int>::iterator it_end)
	{
		using std::move;
		std::ptrdiff_t dist = distance(it_begin, it_end);
		for (--dist; dist > 0; dist -= 2)
		{
			int tmp = move(*it_begin);
			*it_begin++ = move(*--it_end);
			*it_end = move(tmp);
		}
	};
	reverse(v.begin(), v.end());
	cout << " reversed___________________\n" << v;
	qsort(v.data(), v.size(), sizeof(int), [](const void* it1, const void* it2) {
		if ((*static_cast<const int*>(it1)) < (*static_cast<const int*>(it2))) return -1;
		return static_cast<int> ((*static_cast<const int*>(it1)) > (*static_cast<const int*>(it2))); });
	cout << "std::qsort < ______________ \n" << v;
	qsort(v.data(), v.size(), sizeof(int), [](const void* it1, const void* it2) {
		auto res = (*static_cast<const int*>(it1)) <=> (*static_cast<const int*>(it2));
		if (res > 0) return -1;
		return static_cast<int> (res < 0); });
	cout << "std::qsort > _______________\n" << v;
	// #include <algorithm>
	sort(v.begin(), v.end());
	cout << "std::sort___________________\n" << v;
	sort(v.begin(), v.end(), std::greater<>());
	cout << "std::sort std::greater<>()__\n" << v;
	sort(v.begin(), v.end(), std::less<>());
	cout << "std::sort std::less<>()_____\n" << v;
	sort(v.rbegin(), v.rend(), std::less<>());
	cout << "std::sort reverse std::less<>()_____\n" << v;
	sort(v.rbegin(), v.rend(), [](int a, int b) {return a > b; });
	cout << "std::sort reverse return a < b______\n" << v;

	cout << "\n\n";
	cout << " original___________________\n" << v2; // ostream << перегружен для vector
	auto it = remove_if(v2.begin(), v2.end(), [](int elem) {return (elem > 24 && elem < 45); });
	auto d = distance(it, v2.end());
	v2.erase(it, v2.end());
	cout << "std::remove_if___24> x <45___\n" << v2;
	cout << "removed " << d << " elements \n";
	it = remove(v2.begin(), v2.end(), 24); v2.erase(it, v2.end());
	v2.erase(remove(v2.begin(), v2.end(), 46), v2.end());
	cout << "std::remove________24,46____\n" << v2;
}
void mutexLock()
{
	std::vector<std::thread> thr;
	std::vector <std::function<void(int)>> funcs;
	funcs.emplace_back(simpleVolatile1); funcs.emplace_back(simpleVolatile2);
	cleardata();
	cout << "\nожидаем \"_1\" в каждом случае, но получаем нужное только при захвате мьютекса\n\n";
	cout << "start 1 обычные переменные\n";
	for (int i = 0; i < 10; ++i)
	{
		for (auto &elem:funcs)
			thr.emplace_back(elem,i);
	}
	for (auto& elem : thr)
		elem.join();
	thr.clear(); 
	funcs.clear();
	funcs.emplace_back(atomicFlag1); funcs.emplace_back(atomicFlag2);
	cout << "\nend 1\n\n";
	cleardata();
	cout << "start 2 флаги готовности atomic, обычная переменная результата работы \n";
	for (int i = 0; i < 10; ++i)
	{
		for (auto& elem : funcs)
			thr.emplace_back(elem, i);
	}
	for (auto& elem : thr)
		elem.join();
	thr.clear();
	funcs.clear();
	funcs.emplace_back(atomicFlagAndData1); funcs.emplace_back(atomicFlagAndData2);

	cout << "\nend 2\n\n";
	cleardata();
	cout << "start 3 и флаги готовности, и переменная результата работы  atomic\n";
	for (int i = 0; i < 10; ++i)
	{
		for (auto& elem : funcs)
			thr.emplace_back(elem, i);
	}
	for (auto& elem : thr)
		elem.join();
	thr.clear();
	funcs.clear();
	funcs.emplace_back(Mutex1); funcs.emplace_back(Mutex2);
	cout << "\nend 3\n\n";
	cleardata();
	cout << "start Mutex\n";
	for (int i = 0; i < 10; ++i)
	{
		for (auto& elem : funcs)
			thr.emplace_back(elem, i);
	}
	for (auto& elem : thr)
		elem.join();
	thr.clear();
	cout << "\nend Mutex\n";
}
void atomic()
{
	std::vector<std::thread> thr;
	cleardata();
	for (int i = 0; i < 10; ++i)
			thr.emplace_back(fvalatile);
	for (auto& elem : thr)
		elem.join();
	thr.clear();
	cout << "\nсчетчик  count =" << count << "\n";
	for (int i = 0; i < 10; ++i)
		thr.emplace_back(fatomic);
	for (auto& elem : thr)
		elem.join();
	thr.clear();
	cout << "\nсчетчик atomic _count = " << _count << "\n\n";
	cout << "компилятор ";  
	if (_count == count) cout << "не ";
	cout << "оптимизировал выполнение функций\n";
	cout << "разница между счетчиками равна " << _count - count; 

	_count == count ? cout << "\nДЛЯ ДЕМОНСТРАЦИИ СВОЙСТВ atomic ПЕРЕЗАПУСТИТЕ ПРОГРАММУ" << endl:
		cout << " !!!" << endl;

}
void asyncTasks()
{
	std::queue <std::future<int>> qu;
	//const char* str1 = "Каждый охотник желает знать где сидит фазан";
	qu.push(std::async(func, "*1Каждый "));
	qu.push(std::async(func, "*2охотник "));
	qu.push(std::async(func, "*3желает "));
	qu.push(std::async(func, "*4знать "));
	qu.push(std::async(func, "*5где "));
	qu.push(std::async(func, "*6сидит "));
	qu.push(std::async(func, "*7фазан "));
	while (!qu.empty())
	{
		qu.front().wait();
		cout << "длина_" << ++count << "=" << qu.front().get() << endl;
		qu.pop();
	}
	cout <<"\n\n_____std::launch::async______\n\n";
	qu.push(std::async(std::launch::async, func, "*1Каждый "));
	qu.push(std::async(std::launch::async, func, "*2охотник "));
	qu.push(std::async(std::launch::async, func, "*3желает "));
	qu.push(std::async(std::launch::async, func, "*4знать "));
	qu.push(std::async(std::launch::async, func, "*5где "));
	qu.push(std::async(std::launch::async, func, "*6сидит "));
	qu.push(std::async(std::launch::async, func, "*7фазан "));
	{ int count{};
		while (!qu.empty())
		{
			qu.front().wait();
			cout << "длина_" << ++count << "=" << qu.front().get() << endl;
			qu.pop();
		}
	}
}
void timer()
{
	const char* s1 = "сработал ";
	const char* s2 = "таймер  ";
	int (*lambda1) (const char* part1, const char* part2) =
		[](const char* part1, const char* part2)->int {cout << part1 << part2; return 10000; };
	void (*lambda2) (const char* part1, const char* part2) =
		[](const char* part1, const char* part2)  {cout << part1 << part2; };

	cout << "установлен таймер1 функция возвращает значение \n";
	OnTimer <int> _timer1(3000, lambda1, s1,s2);
	for (int i{}; i < 7; ++i)
	{
		cout << i << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	while (!_timer1.IsReady());
	cout <<"функция вернула значение: " << _timer1.GetResult() << endl << endl;

	cout << "установлен таймер2 функция типа void \n";
	OnTimer _timer2(3000, lambda2, s1, s2);
	for (int i{}; i < 7; ++i)
	{
		cout << i << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
void islands()
{
	int size_row = 17, size_col = 20;
	for (int r{}; r < size_row; ++r)
	{
		for (int c{}; c < size_col; ++c)
		{
			if (test_mass[r][c]) cout << "G ";
			else cout <<  "_ ";
		}
		cout << endl;
	}
	cout << endl; cout << endl;
	// статический массив
	Isle isle(test_mass);
	cout << "найдено " << isle.GetIslandsNum() << " островков в статическом массиве\n";
	// динамический массив
	unsigned char** test_dynamicmass;
//	int size_row = 17, size_col = 20;
	test_dynamicmass = new unsigned char* [size_row];
	if (!test_dynamicmass) {cout << "ошибка создания динамического массива в islands()\n"; return;};
	for (int r = 0; r < size_row; ++r)
		test_dynamicmass[r] = new unsigned char[size_col];
	for (int r{}; r < size_row; ++r)
		for (int c{}; c < size_col; ++c)
			test_dynamicmass[r][c] = test_mass[r][c];
	Isle isle2(test_dynamicmass, size_row, size_col);
	cout << "найдено " << isle2.GetIslandsNum() << " островков в динамическом массиве\n";
	// удаление массива
	for (int r = 0; r < size_row; ++r)
		delete[] test_dynamicmass[r];
	delete[] test_dynamicmass;
	// статический массив по указателю 1
	unsigned char (*pointer_to_static)[17][20] = &test_mass;
	Isle isle3(pointer_to_static);
	cout << "найдено " << isle3.GetIslandsNum() << " островков в статическом массиве по указателю unsigned char (*pointer_to_static)[17][20] = &test_mass \n";
	// статический массив по указателю 2
	unsigned char(*pointer_to_static2) [20] = test_mass;
	Isle isle4(pointer_to_static2, size_row);
	cout << "найдено " << isle4.GetIslandsNum() << " островков в статическом массиве по указателю unsigned char (*pointer_to_static2)[20] = test_mass;\n";
}
void mazeGuide()
{
	MazeGuide mazeguide(test_maze, {0,0}, {16,14});
	auto path= mazeguide.FindExit();
	mazeguide.ShowMaze();
	cout <<endl<< path.size()<< endl;

	if (!path.empty());
	for (int i{};i<path.size(); ++i)
	{
		cout << path[i].first << ", " << path[i].second << " | ";
		if (i&&!(i % 10))cout << "\n";
	}
}
void GetSetProperty()
{
	Proper test_property;
	test_property.field_property = 10;
	cout <<"test_property.my_property= " << test_property.field_property <<endl;

	test_property.mass_property[0][0] = 1;
	test_property.mass_property[0][1] = 2;
	test_property.mass_property[1][0] = 3;
	test_property.mass_property[1][1] = 4;

	cout << "test_property.mass_property= \n" << test_property.mass_property[0][0] <<"  " 
		<< test_property.mass_property[0][1] <<  endl<< test_property.mass_property[1][0] << "  "
		<< test_property.mass_property[1][1] << endl;
}