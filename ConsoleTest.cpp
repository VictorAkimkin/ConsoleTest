// ConsoleTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma once
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "MyMath.h"
#include "simplearray.h"
#include "HashTable.h"

void rhombshaped_heritage();
void operators_redefinition();
void hashTable();
int main()
{
	setlocale(LC_ALL, "Rus");
	//
	// ромбовидное наследование: класс наследник от двух классов с общим предком
	rhombshaped_heritage();
	std::cout << "\nrhombshaped_heritage() end \n\n";
	// 
	// перегрузка операторов шаблонного класса с динамическим массивом и перегрузка ostream
	operators_redefinition();
	std::cout << "\noperators_redefinition() end\n\n";
	// 
	// Хэш таблица 
	hashTable();
    std::cout << "\nhashTable() end\n\n";


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
	a[0] = 2; a[1] = 4;
	std::cout << "a =\n" << a;
	std::cout << "\n";

	simplearray <int> b(4);
	b[0] = 3; b[1] = 6; b[2] = 9; b[3] = 12;
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
	d = { 0,1,2 };
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
	HashTable ht(3);
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
}
