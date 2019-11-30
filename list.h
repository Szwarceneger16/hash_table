#pragma once

#ifndef __MY_EXCEPTIONS
#define __MY_EXCEPTIONS

#include <string>

class my_exceptions_class
{
	short i;
	std::string class_name;
public:
	explicit my_exceptions_class(short ii, std::string name) :i(ii), class_name(name) {};
	std::string get_info(void)
	{
		switch (this->i)
		{
		case 1:
			return "Error! " + this->class_name + " is empty!";
			break;
		case 2:
			return "Error! You passed down value out of range of " + this->class_name + "!!!";
			break;
		case 3:
			return "Error! You pass value smaller than 0! Please Kill yoursefl";
			break;
		case 4:
			return "Error! You haven\'t more memory !!!!";
			break;
		case 5:
			return "Error! I wasn\'t find this value !!!!";
			break;
		default:
			return "I don't recognize this error";
			break;
		}
	}
};
#endif // !__MY_EXCEPTIONS


#ifndef __LIST
#define __LIST

template<class T>
class list
{
	template<class I>
	class list_node {
	public:
		I val;
		list_node(list_node<I>* p, list_node<I>* n, I value) :prev(p), next(n), val(value) {};
		list_node(I value) :list_node(NULL, NULL, value) {};
		list_node<I>* next;
		list_node<I>* prev;
		~list_node() {  }
	};

	long size;
	list_node<T>* tail;
	list_node<T>* head;
public:
	list() :tail(NULL), head(NULL), size(0) {};

	void add_tail(const T value)
	{
		if (this->tail == NULL)
		{
			try {
				this->tail = new list_node<T>(value);
			}
			catch (std::bad_alloc & ba) { throw my_exceptions_class(4,"List"); }
			this->head = this->tail;
			this->tail->val = value;

		}
		else
		{
			list_node<T>* tmp = this->tail;
			try {
				this->tail = new list_node<T>(value);
			}
			catch (std::bad_alloc & ba) { throw my_exceptions_class(4,"List"); }
			tmp->next = this->tail;
			this->tail->prev = tmp;
		}
		this->size++;
	};

	void add_head(const T value)
	{
		if (this->head == NULL)
		{
			try {
				this->head = new list_node<T>(value);
			}
			catch (std::bad_alloc &ba) { throw my_exceptions_class(4,"List"); }
			this->tail = this->head;
			this->head->val = value;
		}
		else
		{
			list_node<T>* tmp = this->head;
			try {
				this->head = new list_node<T>(value);
			}
			catch (std::bad_alloc & ba) { throw my_exceptions_class(4,"List"); }
			tmp->prev = this->head;
			this->head->next = tmp;
		}
		this->size++;
	};

	bool add(const T& value, bool (*funkcja) (const T  a, const T  b))
	{
		bool flag = false;
		if (this->head == NULL)
		{
			try {
				this->head = new list_node<T>(value);
			}
			catch (std::bad_alloc & ba) { throw my_exceptions_class(4,"List"); }
			this->tail = this->head;
			this->head->val = value;
			flag = true;
		}
		else
		{
			list_node<T>* scroll = this->head;
			while (scroll)
			{
				if (funkcja(value, scroll->val))
				{
					list_node<T>* tmp = scroll->prev;
					if (tmp == NULL)
					{
						try {
							this->head = scroll->prev = new list_node<T>(NULL, scroll, value);
						}
						catch (std::bad_alloc & ba) { throw my_exceptions_class(4,"List"); }
					}
					else
					{
						try {
							tmp->next = scroll->prev = new list_node<T>(scroll->prev, tmp->next, value);
						}
						catch (std::bad_alloc & ba) { throw my_exceptions_class(4,"List"); }
					}

					flag = true; break;
				}
				scroll = scroll->next;
			}
		}
		if (!flag)
		{
			try {
				this->tail = this->tail->next = new list_node<T>(this->tail, NULL, value);
			}
			catch (std::bad_alloc & ba) { throw my_exceptions_class(4,"List"); }
			flag = true;
		}
		size++;
		return flag;
	};

	bool sort(bool (*funkcja) (const T  a, const T  b))
	{
		list_node<T>* tmp1 = this->head,*tmp2;
		bool change = false;
		while (change)
		{
			change = false;
			while (tmp1->next)
			{
				if (!funkcja(tmp1->val, tmp1->next->val))
				{
					tmp2 = tmp1->next;
					tmp1->next = tmp2->next;
					tmp2->prev = tmp1->prev;
					tmp1->prev = tmp2;
					tmp2->next = tmp1;
					change = true;
				}
				tmp1 = tmp1->next;
			}
		}
		return true;
	}

	T get_tail() { return this->tail->val; };
	T get_head() { return this->tail->val; };
	long get_size() 
	{ 
		return this->size; 
	};

	void print(void (*funkcja) (const T  a))
	{
		list_node<T>* scroll = this->head;;
		while (scroll)
		{
			funkcja(scroll->val);
			scroll = scroll->next;
		}
	};

	bool find_value_bool(const T& value, bool (*funkcja) (const T  a, const T  b))
	{
		list_node<T>* scroll = this->head;
		while (scroll)
		{
			if (funkcja(scroll->val, value)) return true;
			scroll = scroll->next;
		}
		return false;
	}


	T find_value(const T& value, bool (*funkcja) (const T  a, const T  b)) // throw std::invalid_argument
	{
		if (this->size == 0) return NULL;
		list_node<T>* scroll = this->head;
		while (scroll)
		{
			if (funkcja(scroll->val, value))
			{
				return scroll->val;
			}
			scroll = scroll->next;
		}
		//throw my_exceptions_class(2,"List");
		return NULL;
	}

	long find_position(const T& value, bool (*funkcja) (const T  a, const T  b))// throw std::invalid_argument
	{
		long position = 0;
		list_node<T>* scroll = this->head;
		while (scroll)
		{
			if (funkcja(value, scroll->val)) return position;
			position++;
			scroll = scroll->next;
		}
		throw my_exceptions_class(2,"List");
	}

	long long get_element(long long pos)// throw std::out_of_range
	{
		if (pos < 0 || pos > this->size) throw my_exceptions_class(2, "List");
		if (pos < (this->size / 2))
		{
			list_node<T>* scroll = this->head;
			for (long i = 0; i < pos; i++)  scroll = scroll->next;
			return scroll->val;
		}
		else
		{
			list_node<T>* scroll = this->tail;
			for (long i = 0; i < (this->size - pos - 1); i++)  scroll = scroll->prev;
			return scroll->val;
		}
	}

	bool remove_value(const T value, bool (*funkcja) (const T  a, const T  b),bool ptr=false)
	{
		list_node<T>* scroll = this->head, * tmp;
		if (scroll == NULL) return false;
		bool flag = false, flag2 = true;


		if (funkcja(scroll->val, value))
		{
			if (scroll->next != NULL)
			{
				scroll = scroll->next;
				this->head = scroll;
				if (ptr) delete scroll->prev->val;
				delete scroll->prev;
				scroll->prev = NULL;
				this->size--;
			}
			else
			{
				if (ptr) delete scroll->val;
				delete scroll;
				this->head = this->tail = NULL;
				this->size--;
				return true;
			}
		}

		while (scroll->next)
		{
			flag2 = true;
			if (funkcja(scroll->val, value))
			{
				if (!scroll->prev)
				{
					scroll = scroll->next;
					if (ptr) delete scroll->prev->val;
					delete scroll->prev;
					scroll->prev = NULL;
					this->head = scroll;
					this->size--;
					flag2 = false;
				}
				else
				{
					tmp = scroll;
					scroll->next->prev = scroll->prev;
					scroll->prev->next = scroll->next;
					scroll = scroll->next;
					if (ptr) delete tmp->val;
					delete tmp;
					this->size--;
					flag2 = false;
				}
			}
			if (flag2) scroll = scroll->next;
		}

		if (funkcja(scroll->val, value))
		{
			if (scroll->prev != NULL)
			{
				scroll = scroll->prev;
				this->tail = NULL;
				if (ptr) delete scroll->next->val;
				delete scroll->next;
				scroll->next = NULL;
				this->tail = scroll;
			}
			else
			{
				this->tail = this->head = NULL;
				if (ptr) delete scroll->val;
				delete scroll;
			}


			this->size--;
		}

		return flag;
	}

	T remove_position(const long& pos)// throw std::out_of_range
	{
		if (pos < 0 || pos >= this->size) throw my_exceptions_class(2,"list");
		list_node<T>* scroll = this->head, * tmp; T ret;
		for (long i = 0; i < pos; i++) scroll = scroll->next;
		if (!scroll->prev && !scroll->next)
		{
			ret = scroll->val;
			delete scroll;
			this->tail = this->head = NULL;
			this->size--;
			return ret;
		}
		else if (!scroll->prev)
		{		
			scroll = scroll->next;
			ret = scroll->prev->val;
			delete scroll->prev;
			scroll->prev = NULL;
			this->head = scroll;
			this->size--;
			return ret;
		}
		else if (!scroll->next)
		{

			tmp = scroll;
			scroll = scroll->prev;
			this->tail = scroll;
			scroll->next = NULL;
			ret = tmp->val;
			delete tmp;
			this->size--;
			return ret;
		}
		else
		{
			tmp = scroll;
			scroll->next->prev = scroll->prev;
			scroll->prev->next = scroll->next;
			scroll = scroll->next;
			ret = tmp->val;
			delete tmp;
			this->size--;
			return ret;
		}

		return NULL;
	}

	void erase_ptr(void)
	{
		list_node<T>* scroll = this->head;
		if (scroll == NULL) return;

		while (scroll->next)
		{
			scroll = scroll->next;
			delete scroll->prev->val;
			delete scroll->prev;
		}

		delete scroll->val;
		delete scroll;
		this->head = this->tail = NULL;
		this->size = 0;
	}

	void erase(void)
	{
		list_node<T>* scroll = this->head;

		if (scroll == NULL) return;

		while (scroll->next)
		{
			scroll = scroll->next;
			delete scroll->prev;
		}


		delete scroll;
		this->head = this->tail = NULL;
		this->size = 0;
	}


	~list() { };
};
#endif // !__LIST

