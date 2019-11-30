
#include <iostream>
#include "hash_table.h"
#include <time.h>
#include <random>
#include <list>
#include <algorithm>

std::string RandomString(int il_zn = 6)
{
	char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
						  'h', 'i', 'j', 'k', 'l', 'm', 'n',
						  'o', 'p', 'q', 'r', 's', 't', 'u',
						  'v', 'w', 'x', 'y', 'z' };

	std::string res = "";
	for (int i = 0; i < il_zn; i++)
		res = res + alphabet[rand() % 26];
	return res;
}

std::string rand_string(int il_zn = 6)
{
	char pom = 0;
	std::string wyj;
	for (int i = 0; i < il_zn; i++)
	{
		pom = (rand() % 25) + 65;
		wyj += pom;
	}
	return wyj;
}

void printee(const std::string a,const int b)
{
	std::cout << a << ", " << b << " || ";
}

void pr(const std::string a)
{
	std::cout << a << ", ";
}

void pr_int(const int a)
{
	std::cout << a << ", ";
}

void space (void)
{
	std::cout << std::endl;
}


int main()
{
	srand(NULL);
	///*void (*printer_wsk) (const std::string, const int);
	//printer_wsk = &printee;*/
	/*hash_table<std::string, int> tab1;
	tab1.insert(new pair<std::string, int>("abc", 2));
	tab1.insert(new pair<std::string, int>("abd", 8));
	tab1.print(space);*/
	//std::cout << "------------------------------------------------------" << std::endl;
	//tab1.insert(new pair < std::string, int>("bgf", 6));
	//tab1.insert(new pair < std::string, int>("bhj", 12));
	//tab1.insert(new pair < std::string, int>("tyj", 7));

	//tab1.print(space);
	//std::cout << "------------------------------------------------------" << std::endl;
	//try {
	//	std::cout << tab1.find(&pair<std::string, int>("abc", 0))->second << std::endl;
	//}
	//catch (my_exceptions_class & ba) {
	//	std::cout << ba.get_info() << std::endl;
	//}

	//tab1.remove(&pair<std::string, int>("xyz"));
	//
	//std::cout << "------------------------------------------------------" << std::endl;
	//tab1.print(space);

	const int MAX_ORDER = 7;
	clock_t t1, t2;

	std::list< std::string> l1;
	std::list< int> l2(1020,0);
	std::list< std::string>::iterator it1;
	std::list< int>::iterator it2;

	hash_table<std::string, int> tab1;
	srand(clock());

	for (int o = 1; o <= MAX_ORDER; o++)
	{
		const int n = pow(10, o);

		t1 = clock();
		int i;
		for (i = 0; i < n; i++) {
			tab1.insert(new pair<std::string, int>(RandomString(), i)); //l1.push_back(rand_string());
		}
		t2 = clock();
		//std::for_each(l1.begin(), l1.end(), pr);
		//std::transform(l1.begin(), l1.end(), l2.begin(), hash_algorithm);
		//std::for_each(l2.begin(), l2.end(), pr_int);

		tab1.print(space,6);
		std::cout << std::endl;
		std::cout << "Liczba elementow: " << i << " " << tab1.get_size() << " | Czas dodawania elementow: " << (double(t2) - double(t1)) / CLOCKS_PER_SEC << " |-| " << std::endl;

		const int m = pow(10, 4);
		int hits = 0;

		t1 = clock();
		pair<std::string, int>* tmp;
		for (int i = 0; i < m; i++)
		{
			tmp = tab1.find(&pair<std::string, int>(rand_string()));
			if (!tmp) hits++;
		}
		t2 = clock();
		std::cout << tab1.get_hash_tible_size() <<"Liczba trafien: "<< hits << " | Czas wysuzkiwania elementow: " << (double(t2) - double(t1)) / CLOCKS_PER_SEC << " |-| " << std::endl;

		tab1.info();

		std::cout << "-----------------------------------------------------------------------------" << std::endl;

		tab1.erase();
	}
}

