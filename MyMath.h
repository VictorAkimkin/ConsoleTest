#pragma once
#include "Sum.h"
#include "Multiply.h"
// двойное наследование от классов с общим предком
class MyMath :
    public Multiply, public Sum
{
public:
    MyMath() = default;
    MyMath(int x, int y) :Sum(x, y), Multiply(x, y)
    {
       std::cout << "Конструктор MyMath\n";
       SetX(6); SetY(7); std::cout << "MyMath (x,y) подмена значений на 6 и 7\n";
    }
  //  { Sum::x = 6; Calc:Sum::y = 7; Multiply::x = 6; Multiply::y = 7; }
    int multiplyXY() { return Multiply::Result(); }
    int sumXY() { return Sum::Result(); }
    ~MyMath() { std::cout << "Деструктор MyMath\n"; }
};

