#pragma once
#include "Calc.h"
// virtual ����� ��� �������� ������ ���������� ������������� ������ Calc ��� ���� ��������
class Sum : public virtual Calc
{
public:
	Sum() = default;
	Sum(int x, int y) { SetX(x); SetY(y); std::cout << "����������� Sum\n";}
	void Set(int x, int y) {SetX(x); SetY(y);}
	int Result() { return GetX() + GetY(); }

public:
	~Sum() {}
};

