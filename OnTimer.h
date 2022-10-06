#pragma once
#include <chrono>
#include <functional>
#include <thread>
#include <type_traits>

template <class Result=void>
class OnTimer
{
public:
	template <class... fArgs, class... Args>
	OnTimer(int time, void (*f)(fArgs...), Args&&... args)
	{
		auto foo(std::bind(f, std::forward<Args>(args)...));
		if (!std::is_same<void, Result>::value) throw ("OnTimer type and function result type must be the same");
		std::thread([time, foo]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(time));
				foo();
			}).detach();
	}
	template <class Func, class... Args>
	OnTimer(int time, Func&& f, Args&&... args)
	{
		// для C++14 - C++17, не работает в C++20
		//using f_type = std::function <typename std::result_of<Func(Args...)>::type()>;
		// для C++17+, не работает в C++14-
		//using f_type = std::function <typename std::invoke_result<Func, Args...>::type()>;

		//f_type foo(std::bind(std::forward<Func>(f), std::forward<Args>(args)...));
		// 
		// для C++14+
		auto foo(std::bind(std::forward<Func>(f), std::forward<Args>(args)...));
		if (!std::is_same<decltype(foo()), Result>::value) throw ("OnTimer type and function result type must be the same");
		std::thread([time, foo,this]()
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(time));
				this->result = new Result(foo());
				this->ready = true;
			}).detach();
	}
	bool IsReady() {return ready;}
	Result GetResult() {return *result;}
	~OnTimer()
	{
		if (this->result) delete this->result;
	}
private:
	volatile bool ready{};
	Result* result{};
};

