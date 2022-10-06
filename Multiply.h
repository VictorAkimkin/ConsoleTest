#pragma once
#include "Calc.h"
// virtual нужно для создания одного экземпляра родительского класса Calc для всех потомков
class Multiply: public virtual Calc
{
public:
	Multiply() = default;
	Multiply(int x, int y) { SetX(x); SetY(y); std::cout << "Конструктор Multiply\n";}
	void Set(int x, int y)	{SetX(x); SetY(y);}
	int Result() { return GetX() * GetY(); }

public:
	~Multiply() { std::cout << "Деструктор Multiply\n"; }

};

