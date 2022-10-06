#pragma once
#include <iostream>

using std::cout;
using std::endl;

int func(const char* str)
{
	cout << str<<" thread ID: " << std::this_thread::get_id() << endl;
	return strlen(str);
}
