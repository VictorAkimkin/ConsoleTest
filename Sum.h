#pragma once
#include "Calc.h"
// virtual нужно для создания одного экземпляра родительского класса Calc для всех потомков
class Sum : public virtual Calc
{
public:
	Sum() = default;
	Sum(int x, int y) { SetX(x); SetY(y); std::cout << "Конструктор Sum\n";}
	void Set(int x, int y) {SetX(x); SetY(y);}
	int Result() { return GetX() + GetY(); }

public:
	~Sum() {}
};

