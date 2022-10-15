#pragma once
#include <iostream>
void iFC(float&& f) { std::cout << "float= " << f << std::endl; }
void iFC(int&& i) { std::cout << "int= " << i << std::endl; }

template <typename... T>
void convert(T &&... x)
{
	(iFC(x), ...); // конвертирует float в int&& и вызывает f(int&&), конвертирует int в float&& и вызывает f(float&&)
	(iFC(std::forward<T>(x)), ...);// передает float как float&&, а int как int&& с соответсвующими вызами f
}
