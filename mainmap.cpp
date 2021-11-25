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
	ft::map<int, std::string>::iterator it;

	//it++;
	//it++;

	ft::pair<int, std::string> p1(1, "foo");
	mapp.insert(p1);

	it = mapp.begin();
	//mapp.insert(std::pair{2, "bar"});
	//mapp.insert(std::pair{3, "baz"});
	//mapp.insert(std::pair{4, "lol"});
	//mapp.insert(std::pair{5, "meuh"});

	//std::cout << "iterator = " << it->first <<std::endl;

	return 0;
}