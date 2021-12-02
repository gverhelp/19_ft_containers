#include "include/map.hpp"
#include <map>
#include <iostream>

int main()
{
	/* Test vector
	std::vector<std::string> vec;
	std::vector<std::string>::iterator it;
​
	std::cout << "cap = " << vec.capacity() << std::endl;
	vec.push_back("hello");
	vec.push_back("world");
	vec.push_back("foo");
	vec.push_back("baz");
	vec.push_back("bar");
​
	
	it = vec.begin();
	//print_vec(vec);
	it = vec.erase(it + 1);
	print_vec(vec);
	std::cout << "cap = " << vec.capacity() << std::endl;
	std::cout << "size = " << vec.size() << std::endl;
	std::cout << "it = " << *it << std::endl;
​
	vec.assign(2, "lol");
	std::cout << "cap = " << vec.capacity() << std::endl;
	std::cout << "size = " << vec.size() << std::endl;
	std::cout << "it = " << *it << std::endl;
	*/

	/*Test map*/
	ft::map<int, std::string> mapp;
	ft::map<char, int>::iterator it;
	ft::map<char, int>::iterator it2;

	//it++;
	//it++;

	//ft::pair<int, std::string> p1(1, "foo");
	//ft::pair<int, std::string> p2(2, "xd");
//	mapp.insert(p1);
//	mapp.insert(p2);

	// it = mapp.begin();
	// std::cout << it->first << std::endl;
	// std::cout << it->second << std::endl;
	// it++;
	// it--;
	// std::cout << it->first << std::endl;
	// std::cout << it->second << std::endl;
	//mapp.insert(std::pair{2, "bar"});
	//mapp.insert(std::pair{3, "baz"});
	//mapp.insert(std::pair{4, "lol"});
	//mapp.insert(std::pair{5, "meuh"});

	//std::cout << "iterator = " << it->first <<std::endl;
	ft::map<char, int> first;
	//int i = 0;

	//mapp['a'] = "lol";
	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;
	first['e'] = 80;
	first['f'] = 10;
	first['g'] = 30;
	first['h'] = 50;
	first['i'] = 70;
	first['j'] = 80;
	first['k'] = 10;
	first['l'] = 30;
	first['m'] = 50;
	first['n'] = 70;
	first['o'] = 80;
	it = first.begin();
	it2 = first.end();
	first.debug();
	std::cout << "lol meuh : " << it2.base() << std::endl;
	 while (it != it2)
	 {
	 	std::cout << it->first << std::endl;
	 	std::cout << it->second << std::endl;
	 	it++;
		std::cout << "it.nase : " << it.base() << std::endl;
	 	//i++;
	 }
	 //it = first.end();
	 std::cout << it2->first << std::endl;
	 std::cout << it2->second << std::endl;

	//end = last_elem++;
	//last_node;
	return 0;
}
