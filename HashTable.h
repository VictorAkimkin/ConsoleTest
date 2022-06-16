#pragma once
#include <list>
#include <string>
#include <iostream>
#define _CLT_NAME_STD_LEN 35

class HashTable
{
	public:
	explicit HashTable(unsigned  int size);
	HashTable(const HashTable& ) = delete;
	HashTable(const HashTable&&) = delete;
	void operator=(const HashTable&) = delete;
	void operator=(const HashTable&&) = delete;
	~HashTable();
	// methods
	bool isEmpty();
	bool erase(std::string client); // true- если удалось стереть запись
	bool addnew(std::string client, std::string data);//true- если запись новая
	unsigned int size() const;
	void print_table();
	std::string report();
private:
	// methods
	unsigned long int _hash_function(std::string str);
	// values
	unsigned int _TABLE_SIZE{};
	std::list <std::pair<std::string, std::string>>* TABLE{};
	std::string last_operation_report{};
};

