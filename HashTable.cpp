#include "HashTable.h"

HashTable::HashTable(unsigned int size):_TABLE_SIZE(size), TABLE (new std::list <std::pair<std::string, std::string>> [size])
{
}

HashTable::~HashTable()
{
	if (TABLE) { delete[] TABLE; TABLE = nullptr;}
}

bool HashTable::isEmpty()
{
	for (int i{}; i < _TABLE_SIZE; ++i)
	  {
		 if (TABLE[i].size()) return false;
	  }
	return true;
}

bool HashTable::erase(std::string client)
{
	//if (isEmpty()) return false; 
	auto index = _hash_function(client);
	auto &list = TABLE[index];
	auto itr = begin(list);
	for (;itr!=end(list);++itr)
	  if (itr->first == client)
		{ 
			itr = list.erase(itr);
			last_operation_report= "Запись клиента [" + client + "] удалена.";
			return true;
		}
	if (isEmpty())last_operation_report = "Таблица пустая. "; else last_operation_report = "Не удалось найти запись ";
	last_operation_report += "Запись клиента [" + client +"] не удалена.";
	return false;
}

bool HashTable::addnew(std::string client, std::string data)
{
	auto index = _hash_function(client);
	auto& list = TABLE[index];
	auto itr = begin(list);
	for (; itr != end(list); ++itr)
		if (itr->first == client)
		{
			itr->second=data;
			last_operation_report = "Клиент [" + client+"] уже существует в базе. Данные записи обновлены";
			return false;
		}
	list.emplace_back(client,data);
	last_operation_report = "Добавлена новая запись. Клиент ["+ client+"]";
	return true;
}

unsigned int HashTable::size()const
{
	return _TABLE_SIZE;
}

void HashTable::print_table()
{
	for (int i{}; i < _TABLE_SIZE; ++i)
	{
		if (TABLE[i].size())
		{
			for (auto &elem: TABLE[i])
			{
				std::string client= elem.first + " :";
				if (client.length() < _CLT_NAME_STD_LEN) client.resize(_CLT_NAME_STD_LEN, ' ');
				std::string out= client+"  [" + elem.second +"]"+"\n";
				std::cout<<out;
			}
		}

	}

}

unsigned long int HashTable::_hash_function(std::string str)
{
	unsigned long int res{};
	for (int i = 0; i < str.length() && (unsigned char)str[i]>31; ++i)
	  res += str[i] - 31;
	return res%_TABLE_SIZE;
}

std::string HashTable::report()
{
	return last_operation_report;
}
