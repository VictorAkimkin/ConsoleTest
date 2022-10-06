#pragma once
#include "Calc.h"
// virtual ����� ��� �������� ������ ���������� ������������� ������ Calc ��� ���� ��������
class Multiply: public virtual Calc
{
public:
	Multiply() = default;
	Multiply(int x, int y) { SetX(x); SetY(y); std::cout << "����������� Multiply\n";}
	void Set(int x, int y)	{SetX(x); SetY(y);}
	int Result() { return GetX() * GetY(); }

public:
	~Multiply() { std::cout << "���������� Multiply\n"; }

};

