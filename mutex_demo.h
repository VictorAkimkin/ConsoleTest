#pragma once
#include <iostream>
#include <mutex>
volatile std::atomic <int> _data{};
volatile std::atomic <bool> _flag{};
volatile int data{};
volatile bool flag{};
std::mutex mu;

using std::cout;
using std::endl;

void cleardata()
{
	data = 0; _data = 0; flag = false; _flag = false;
}
void simpleVolatile1(int in)
{
	if (flag) return;
	++data;
	flag = true;
}
void simpleVolatile2(int in)
{
	if (flag)
	{
		cout << in << "_" << data << endl;
		data = 0;
		flag = false;
	}
}
void atomicFlag1(int in)
{
	if (_flag.load(std::memory_order_acquire)) return;
	++data;
	_flag.store(true, std::memory_order_release);
}
void atomicFlag2(int in)
{
	if (_flag.load(std::memory_order_acquire))
	{
		cout << in << "_" << data << endl;
		data = 0;
		_flag.store(false, std::memory_order_release);
	}
}
void atomicFlagAndData1(int in)
{
	if (_flag.load(std::memory_order_seq_cst)) return;
	++_data;
	_flag.store(true, std::memory_order_seq_cst);
}
void atomicFlagAndData2(int in)
{
	if (_flag.load(std::memory_order_seq_cst))
	{
		cout << in << "_" << _data << endl;
		_data.store(0, std::memory_order_seq_cst);
		_flag.store(false, std::memory_order_seq_cst);
	}
}
void Mutex1(int in)
{
	const std::lock_guard<std::mutex> lock(mu);
	if (flag) return;//while создает бесконечный цикл
	data = 1;
	flag = true;
}
void Mutex2(int in)
{
	mu.lock();
	if (flag)//while создает бесконечный цикл
	{
		flag = false; // можно не переносить в конец условия.
		cout << in << "_" << data << endl;
		data = 0;
	}
	mu.unlock();
}

