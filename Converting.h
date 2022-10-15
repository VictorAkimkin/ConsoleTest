#pragma once
#include <iostream>
void iFC(float&& f) { std::cout << "float= " << f << std::endl; }
void iFC(int&& i) { std::cout << "int= " << i << std::endl; }

template <typename... T>
void convert(T &&... x)
{
	(iFC(x), ...); // ������������ float � int&& � �������� f(int&&), ������������ int � float&& � �������� f(float&&)
	(iFC(std::forward<T>(x)), ...);// �������� float ��� float&&, � int ��� int&& � ��������������� ������ f
}
