#pragma once
#include "Sum.h"
#include "Multiply.h"
// ������� ������������ �� ������� � ����� �������
class MyMath :
    public Multiply, public Sum
{
public:
    MyMath() = default;
    MyMath(int x, int y) :Sum(x, y), Multiply(x, y)
    {
       std::cout << "����������� MyMath\n";
       SetX(6); SetY(7); std::cout << "MyMath (x,y) ������� �������� �� 6 � 7\n";
    }
  //  { Sum::x = 6; Calc:Sum::y = 7; Multiply::x = 6; Multiply::y = 7; }
    int multiplyXY() { return Multiply::Result(); }
    int sumXY() { return Sum::Result(); }
    ~MyMath() { std::cout << "���������� MyMath\n"; }
};

