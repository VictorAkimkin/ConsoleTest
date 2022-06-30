﻿// ConsoleTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma once
#include <iostream>
#include <tuple>


#include "MyMath.h"
#include "simplearray.h"
#include "HashTable.h"
#include "VariadicTemplate.h"

void rhombshaped_heritage();
void operators_redefinition();
void hashTable();
void variadic_template();


int main()
{
	//setlocale(LC_ALL, "Rus");
	////
	//// ромбовидное наследование: класс наследник от двух классов с общим предком
	//rhombshaped_heritage();
	//std::cout << "\nrhombshaped_heritage() end \n\n";
	//// 
	// перегрузка операторов шаблонного класса с динамическим массивом и перегрузка ostream
	//operators_redefinition();
	//std::cout << "\noperators_redefinition() end\n\n";
	//// 
	//// Хэш таблица 
	//hashTable();
    //   std::cout << "\nhashTable() end\n\n";
	//// 
	//// Variadic template и кортежи
	//variadic_template();
	//std::cout << "\nvariadic_template() end\n\n";


	std::cout << "\n\n"; system("pause");
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