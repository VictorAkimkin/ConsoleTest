#pragma once
#include <iostream>

// std::tuple
template<std::size_t I = 0, class... Args>
typename std::enable_if<I == sizeof...(Args)>::type
print_tuple(std::tuple<Args...>& args)
{}

template<std::size_t I = 0, class... Args>
typename std::enable_if < I<sizeof...(Args)>::type
	print_tuple(std::tuple<Args...>& args)
{
	std::cout << std::get<I>(args) << "  \n";;
	print_tuple<I+1, Args...>(args);
}
// --------------------------------------
// Variadic template
template <class T>
void print_tuple(T&&  arg)
{
	std::cout << arg << "  \n";
}

template <class FirstArg, class... Args>
void print_tuple(FirstArg&& first_arg, Args&&... args)
{
	std::cout << first_arg << "  \n";
	print_tuple(args...);
}

template <class FirstArg>
void print_tuple(FirstArg& arg)
{
	std::cout << arg << "  \n";
}

template <class FirstArg, class... Args>
void print_tuple(FirstArg& first_arg, Args&... args)
{
	std::cout << first_arg << "  \n";
	print_tuple(args...);
}
// --------------------------------------
