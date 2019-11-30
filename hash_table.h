#pragma once
#include "list.h"
#include <cstdio>

template <class T, class U>
class pair
{
public:
	T first;
	U second;
	pair(T f, U s) :first(f), second(s) {};
	pair(T f) :pair(f, NULL) {};
};

template <class T, class U>
class hash_table
{
	void static printer(pair<T, U>* a)
	{
		std::cout << a->first << ", " << a->second << " || ";
	}

	bool static cmp_equal(pair<T, U>* a, pair<T, U>* b)
	{
		return a->first == b->first;
	}

	list<pair<T, U>*>* array_pointer;
	int hash_size;
	int current;

	int hash_algorithm(std::string input, int hs)
	{
		int length = input.length() - 1;long long hash_sum = 0;
		for (int i = length; i >= 0; i--)
		{
			hash_sum += ((long long)input[length-i]*pow(31,i));
		}
		hash_sum = hash_sum % hs;
		if (hash_sum > hs) throw my_exceptions_class(1, "hash_table");
		return (int)hash_sum;
	}

	void rehash_table(void)
	{
		list<pair<T, U>*>* tmp_array_pointer = new list<pair<T, U>*>[(this->hash_size*2)]();
		pair<T, U>* tmp;
		for (int i = 0; i < this->hash_size; i++)
		{
			while (array_pointer[i].get_size()>0)
			{
				tmp = array_pointer[i].remove_position(0);
				tmp_array_pointer[(this->hash_algorithm(tmp->first, ((this->hash_size)*2)))].add_head(tmp);		
			}
		}
		this->~hash_table();
		this->array_pointer = tmp_array_pointer;
		this->hash_size *= 2;
	}

public:
	hash_table(int size = 256):hash_size(size),current(0)
	{
		this->array_pointer = new list<pair<T, U>*>[this->hash_size]();
	}

	int get_hash_tible_size(void) const
	{
		return this->hash_size;
	}

	void insert(pair<T, U>* val)
	{
		if ((0.75 * hash_size) < current) rehash_table();
		int hash = this->hash_algorithm(val->first,this->hash_size);
			pair<T, U>* tmp = array_pointer[hash].find_value(val, cmp_equal);
			if (!tmp) { 
				array_pointer[hash].add_head(val); current++;
			}
			else tmp = val;	
	}

	bool remove(pair<T, U>* val)
	{
		bool ret=0;
		for (int i = 0; i < this->hash_size; i++)
		{
			ret = array_pointer[i].remove_value(val, cmp_equal,true);
		}
		return ret;
	}

	pair<T, U>* find(pair<T, U>* val)
	{
		pair<T, U>* ret = NULL;
		ret = array_pointer[(this->hash_algorithm(val->first, this->hash_size))].find_value(val, cmp_equal);
		return ret;
	}

	int get_size(void) const
	{
		int size=0;
		for (int i = 0; i < this->hash_size; i++)
		{
			size+=array_pointer[i].get_size();
		}
		return size;
	}

	void erase(void)
	{
		for (int i = 0; i < this->hash_size; i++)
		{
			array_pointer[i].erase_ptr();
		}

		this->current = 0;
	}

	void print(void (*funkcja)(void))
	{
		for (int i = 0; i < this->hash_size; i++)
		{
			array_pointer[i].print(printer);
			if(array_pointer[i].get_size()) funkcja();
		}
	}

	void print(void (*funkcja)(void),int size)
	{
		for (int i = 0; i < this->hash_size; i++)
		{
			if (size == 0) break;
			array_pointer[i].print(printer);
			if (array_pointer[i].get_size()) {
				funkcja(); size--;
			}
		}
	}

	void info(void)
	{
		int puste = 0, min = 0, max = 0, elementy = 0; double srednia=0.0;
		for (int i = 0; i < this->hash_size; i++)
		{
			if (array_pointer[i].get_size() == 0) { puste++; }
			else
			{
				elementy += array_pointer[i].get_size();
			}


			if (array_pointer[i].get_size() > max) 
			{ 
				max = array_pointer[i].get_size();  
			}
			else if (array_pointer[i].get_size() < min) 
			{ 
				min = array_pointer[i].get_size(); 
			}
			
		}
		if (puste == this->hash_size) srednia = 0;
		else srednia = double(elementy) / (int(hash_size) - puste);
		std::cout << "Elementow: " << elementy << " | Puste: " << puste << " | Min: " << min << " | Max: " << max << " | srednia: " << srednia << std::endl;
	}

	~hash_table()
	{
		for (int i = 0; i < this->hash_size; i++)
		{
			array_pointer[i].erase_ptr();
		}
		delete[] this->array_pointer;
	}
};

