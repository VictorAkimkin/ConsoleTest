#pragma once
#include <atomic>

volatile std::atomic <int>  _count{};
volatile int count{};

void fatomic()
{
	for (int i{}; i < 10000; ++i)
		_count += i;
}

void fvalatile()
{
	for (int i{}; i < 10000; ++i)
		count += i;
}

