#pragma once
#include <iostream>
class Calc
{
private:
	int x, y;
public:
	Calc(): x(0), y(0) {std::cout << "Конструктор Calc (0,0)\n";}
	Calc(int x, int y) :x(x),y(y) { std::cout << "Конструктор Calc (x,y)\n";}

protected:
	void SetX(int x)
	{
		this->x = x;
	}
	void SetY(int y)
	{
		this->y = y;
	}
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}

public:
	~Calc() {}// = delete;

};

