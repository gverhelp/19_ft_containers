#include <iostream>

#include <stack>
#include <vector>
#include <map>

#include "include/stack.hpp"
#include "include/vector.hpp"
#include "include/map.hpp"

#ifndef NAMESPACE
# define NAMESPACE ft
#endif

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//                                                                                  //
//                                    STACK                                         //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void empty_test_stack()
{
    NAMESPACE::stack<int> mystack;
	int sum(0);

	for (int i = 1; i <= 10; i++)
		mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}
	std::cout << "Total: " << sum << std::endl;
}

void size_test_stack()
{
	NAMESPACE::stack<int> myints;
	std::cout << "0. size: " << myints.size() << std::endl;

	for (int i = 0; i < 5; i++)
		myints.push(i);
	std::cout << "1. size: " << myints.size() << std::endl;

	myints.pop();
	std::cout << "2. size: " << myints.size() << std::endl;
}

void top_test_stack()
{
	NAMESPACE::stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;

	std::cout << "mystack.top() is now " << mystack.top() << '\n';
}

void test_push_and_pop_stack()
{
	NAMESPACE::stack<int> mystack;

	for (int i = 0; i < 5; ++i)
		mystack.push(i);

	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
    std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//                                                                                  //
//                                    VECTOR                                        //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

template <class T>
void print_vector(NAMESPACE::vector<T> v)
{
	typename NAMESPACE::vector<T>::iterator it;

	for (it = v.begin(); it != v.end(); it++)
		std::cout << *it << ", ";
	std::cout << std::endl;
}

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename NAMESPACE::enable_if<NAMESPACE::is_integral<T>::value, bool>::type is_odd(T i)
{
	return bool(i % 2);
}

// 2. the second template argument is only valid if T is an integral type:
template <class T>
bool is_even(T i, typename NAMESPACE::enable_if<NAMESPACE::is_integral<T>::value>::type* = NULL)
{
	return !bool(i % 2);
}

void test_constructor_vector()
{
	// constructors used in the same order as described above:
	NAMESPACE::vector<int> first;                               // empty vector of ints
	NAMESPACE::vector<int> second((size_t)4, 100);              // four ints with value 100
	NAMESPACE::vector<int> third(second.begin(), second.end()); // iterating through second
	NAMESPACE::vector<int> fourth(third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16, 2, 77, 29};
	NAMESPACE::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

	std::cout << "The contents of fifth are:";
	for (NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_assignment_operator_vector()
{
	NAMESPACE::vector<int> foo(3, 0);
	NAMESPACE::vector<int> bar(5, 0);

	bar = foo;
	foo = NAMESPACE::vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void test_begin_vector()
{
	NAMESPACE::vector<int> myvector;
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i);

	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_end_vector()
{
	NAMESPACE::vector<int> myvector;
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i);

	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_rbegin_vector()
{
	NAMESPACE::vector<int> myvector(5); // 5 default-constructed ints

	int i = 0;

	NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit != myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_rend_vector()
{
	NAMESPACE::vector<int> myvector(5); // 5 default-constructed ints

	NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();

	int i = 0;
	for (rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
		*rit = ++i;

	std::cout << "myvector contains:";
	for (NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_size_vector()
{
	NAMESPACE::vector<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i = 0; i < 10; i++)
		myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert(myints.end(), 10, 100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';
}

void test_max_size_vector()
{
	NAMESPACE::vector<int> myvector;

	// set some content in the vector:
	for (int i = 0; i < 100; i++)
		myvector.push_back(i);

	std::cout << "size: " << myvector.size() << "\n";
	// std::cout << "capacity: " << myvector.capacity() << "\n";
	// std::cout << "max_size: " << myvector.max_size() << "\n";
}

void test_resize_vector()
{
	NAMESPACE::vector<int> myvector;

	// set some initial content:
	for (int i = 1; i < 10; i++)
		myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8, 100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (size_t i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void test_capacity_vector()
{
	NAMESPACE::vector<int> myvector;

	// set some content in the vector:
	for (int i = 0; i < 100; i++)
		myvector.push_back(i);

	std::cout << "size: " << (int)myvector.size() << '\n';
	// std::cout << "capacity: " << (int)myvector.capacity() << '\n';
	std::cout << "max_size: " << (int)myvector.max_size() << '\n';
}

void test_empty_vector()
{
	NAMESPACE::vector<int> myvector;
	int sum(0);

	for (int i = 1; i <= 10; i++)
		myvector.push_back(i);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	std::cout << "total: " << sum << '\n';
}

void test_reserve_vector()
{
	NAMESPACE::vector<int>::size_type sz;

	NAMESPACE::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	NAMESPACE::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100); // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		bar.push_back(i);
		if (sz != bar.capacity())
		{
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

void test_subscript_operator_vector()
{
	NAMESPACE::vector<int> myvector(10); // 10 zero-initialized elements

	NAMESPACE::vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i = 0; i < sz; i++)
		myvector[i] = i;

	// reverse vector using operator[]:
	for (unsigned i = 0; i < sz / 2; i++)
	{
		int temp;
		temp = myvector[sz - 1 - i];
		myvector[sz - 1 - i] = myvector[i];
		myvector[i] = temp;
	}

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < sz; i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void test_at_vector()
{
	NAMESPACE::vector<int> myvector(10); // 10 zero-initialized ints

	// assign some values:
	for (unsigned i = 0; i < myvector.size(); i++)
		myvector.at(i) = i;

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';
}

void test_front_vector()
{
	NAMESPACE::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	myvector.front() -= myvector.back();

	std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void test_back_vector()
{
	NAMESPACE::vector<int> myvector;

	myvector.push_back(10);

	while (myvector.back() != 0)
	{
		myvector.push_back(myvector.back() - 1);
	}

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void test_assign_vector()
{
	NAMESPACE::vector<int> first;
	NAMESPACE::vector<int> second;
	NAMESPACE::vector<int> third;

	first.assign(7, 100); // 7 ints with a value of 100

	NAMESPACE::vector<int>::iterator it;
	it = first.begin() + 1;

	second.assign(it, first.end() - 1); // the 5 central values of first

	int myints[] = {1776, 7, 4};
	third.assign(myints, myints + 3); // assigning from array.

	std::cout << "Size of first: " << int(first.size()) << '\n';
	std::cout << "Size of second: " << int(second.size()) << '\n';
	std::cout << "Size of third: " << int(third.size()) << '\n';
}

void test_push_back_vector()
{
	NAMESPACE::vector<int> myvector;
	int myint;

	std::cout << "Please enter some integers (enter 0 to end):\n";

	do
	{
		std::cin >> myint;
		myvector.push_back(myint);
	} while (myint);

	std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
}

void test_pop_back_vector()
{
	NAMESPACE::vector<int> myvector;
	int sum(0);
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	std::cout << "The elements of myvector add up to " << sum << '\n';
}

void test_insert_vector()
{
	NAMESPACE::vector<int> myvector(3, 100);
	NAMESPACE::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert(it, 200);

	myvector.insert(it, 2, 300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	NAMESPACE::vector<int> anothervector(2, 400);
	myvector.insert(it + 2, anothervector.begin(), anothervector.end());

	int myarray[] = {501, 502, 503};
	myvector.insert(myvector.begin(), myarray, myarray + 3);

	std::cout << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_erase_vector()
{
	NAMESPACE::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++)
		myvector.push_back(i);

	// erase the 6th element
	myvector.erase(myvector.begin() + 5);

	// erase the first 3 elements:
	myvector.erase(myvector.begin(), myvector.begin() + 3);

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void test_swap_vector()
{
	NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
	NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200
	NAMESPACE::vector<int>::iterator it = foo.begin();
	std::cout << "*it: " << *it << std::endl;
	foo.swap(bar);
	std::cout << "*it: " << *it << std::endl;

	std::cout << "foo contains:";
	for (unsigned i = 0; i < foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i = 0; i < bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';
}

void test_clear_vector()
{
	NAMESPACE::vector<int> myvector;
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.clear();
	myvector.push_back(1101);
	myvector.push_back(2202);

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void test_get_allocator_vector()
{
	NAMESPACE::vector<int> myvector;
	int *p;
	unsigned int i;

	// allocate an array with space for 5 elements using vector's allocator:
	p = myvector.get_allocator().allocate(5);

	// construct values in-place on the array:
	for (i = 0; i < 5; i++)
		myvector.get_allocator().construct(&p[i], i);

	std::cout << "The allocated array contains:";
	for (i = 0; i < 5; i++)
		std::cout << ' ' << p[i];
	std::cout << '\n';

	// destroy and deallocate:
	for (i = 0; i < 5; i++)
		myvector.get_allocator().destroy(&p[i]);
	myvector.get_allocator().deallocate(p, 5);
}

void test_swap_non_member_vector()
{
	//   unsigned int i;
	NAMESPACE::vector<int> foo(3, 100); // three ints with a value of 100
	NAMESPACE::vector<int> bar(5, 200); // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (NAMESPACE::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "bar contains:";
	for (NAMESPACE::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_enable_if_and_is_integral_vector()
{
	// float i = 1; // code does not compile if type of i is not integral
	short int i = 1;

	std::cout << std::boolalpha;
	std::cout << "i is odd: " << is_odd(i) << std::endl;
	std::cout << "i is even: " << is_even(i) << std::endl;
}

void test_reverse_iterator_relational_operators_vector()
{
	NAMESPACE::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	NAMESPACE::vector<int>::const_iterator c_it1 = v.begin();
	NAMESPACE::vector<int>::const_iterator c_it2 = v.begin() + 1;
	std::cout << "(c_it1 == c_it2): " << (c_it1 == c_it2) << std::endl;
	std::cout << "(c_it1 >= c_it2): " << (c_it1 >= c_it2) << std::endl;
	std::cout << "(c_it1 <= c_it2): " << (c_it1 <= c_it2) << std::endl;
	std::cout << "(c_it1 < c_it2): " << (c_it1 < c_it2) << std::endl;
	std::cout << "(c_it1 > c_it2): " << (c_it1 > c_it2) << std::endl;
	std::cout << "(c_it1 - c_it2): " << (c_it1 - c_it2) << std::endl;

	NAMESPACE::vector<int>::iterator it = v.begin() + 1;
	std::cout << "(c_it1 == it): " << (c_it1 == it) << std::endl;
	std::cout << "(c_it1 >= it): " << (c_it1 >= it) << std::endl;
	std::cout << "(c_it1 <= it): " << (c_it1 <= it) << std::endl;
	std::cout << "(c_it1 < it): " << (c_it1 < it) << std::endl;
	std::cout << "(c_it1 > it): " << (c_it1 > it) << std::endl;
	std::cout << "(c_it1 - it): " << (c_it1 - it) << std::endl;
	
	std::cout << "(it == c_it1): " << (it == c_it1) << std::endl;
	std::cout << "(it >= c_it1): " << (it >= c_it1) << std::endl;
	std::cout << "(it <= c_it1): " << (it <= c_it1) << std::endl;
	std::cout << "(it < c_it1): " << (it < c_it1) << std::endl;
	std::cout << "(it > c_it1): " << (it > c_it1) << std::endl;
	std::cout << "(it - c_it1): " << (it - c_it1) << std::endl;

	NAMESPACE::vector<int>::reverse_iterator r_it = v.rbegin();
	NAMESPACE::vector<int>::const_reverse_iterator c_r_it = v.rbegin() + 1;
	std::cout << "(c_r_it == r_it): " << (c_r_it == r_it) << std::endl;
	std::cout << "(c_r_it >= r_it): " << (c_r_it >= r_it) << std::endl;
	std::cout << "(c_r_it <= r_it): " << (c_r_it <= r_it) << std::endl;
	std::cout << "(c_r_it < r_it): " << (c_r_it < r_it) << std::endl;
	std::cout << "(c_r_it > r_it): " << (c_r_it > r_it) << std::endl;
	std::cout << "(c_r_it - r_it): " << (c_r_it - r_it) << std::endl;
	
	std::cout << "(r_it == c_r_it): " << (r_it == c_r_it) << std::endl;
	std::cout << "(r_it >= c_r_it): " << (r_it >= c_r_it) << std::endl;
	std::cout << "(r_it <= c_r_it): " << (r_it <= c_r_it) << std::endl;
	std::cout << "(r_it < c_r_it): " << (r_it < c_r_it) << std::endl;
	std::cout << "(r_it > c_r_it): " << (r_it > c_r_it) << std::endl;
	std::cout << "(r_it - c_r_it): " << (r_it - c_r_it) << std::endl;

	NAMESPACE::vector<int>::const_reverse_iterator c_r_it2 = v.rbegin() + 2;
	std::cout << "(c_r_it == c_r_it2): " << (c_r_it == c_r_it2) << std::endl;
	std::cout << "(c_r_it >= c_r_it2): " << (c_r_it >= c_r_it2) << std::endl;
	std::cout << "(c_r_it <= c_r_it2): " << (c_r_it <= c_r_it2) << std::endl;
	std::cout << "(c_r_it < c_r_it2): " << (c_r_it < c_r_it2) << std::endl;
	std::cout << "(c_r_it > c_r_it2): " << (c_r_it > c_r_it2) << std::endl;
	std::cout << "(c_r_it - c_r_it2): " << (c_r_it - c_r_it2) << std::endl;
	
	std::cout << "(c_r_it2 == c_r_it): " << (c_r_it2 == c_r_it) << std::endl;
	std::cout << "(c_r_it2 >= c_r_it): " << (c_r_it2 >= c_r_it) << std::endl;
	std::cout << "(c_r_it2 <= c_r_it): " << (c_r_it2 <= c_r_it) << std::endl;
	std::cout << "(c_r_it2 < c_r_it): " << (c_r_it2 < c_r_it) << std::endl;
	std::cout << "(c_r_it2 > c_r_it): " << (c_r_it2 > c_r_it) << std::endl;
	std::cout << "(c_r_it2 - c_r_it): " << (c_r_it2 - c_r_it) << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//                                                                                  //
//                                      MAP                                         //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{
		return lhs < rhs;
	}
};

void test_constructors_map(void)
{

	NAMESPACE::map<char, int> first;

	first['a'] = 10;
	first['b'] = 30;
	first['c'] = 50;
	first['d'] = 70;

	NAMESPACE::map<char, int> second(first.begin(), first.end());
	
	NAMESPACE::map<char, int> third(second);
	
	NAMESPACE::map<char, int, classcomp> fourth; // class as Compare

	bool (*fn_pt)(char, char) = fncomp;
	NAMESPACE::map<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare

	// show content:
	std::cout << "first\n";
	for (NAMESPACE::map<char, int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "second\n";
	for (NAMESPACE::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "third\n";
	for (NAMESPACE::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "fourth\n";
	for (NAMESPACE::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << "fifth\n";
	for (NAMESPACE::map<char, int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void test_assignment_operator_map(void)
{
	NAMESPACE::map<char, int> first;
	NAMESPACE::map<char, int> second;

	first['x'] = 8;
	first['y'] = 16;
	first['z'] = 32;

	second = first;				  // second now contains 3 ints
	first = NAMESPACE::map<char, int>(); // and first is now empty

	std::cout << "Size of first: " << first.size() << '\n';
	std::cout << "Size of second: " << second.size() << '\n';
}

void test_begin_end_map(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (NAMESPACE::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void test_rbegin_rend_map(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	// show content:
	NAMESPACE::map<char, int>::reverse_iterator rit;
	for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';
}

void test_empty_map(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;

	while (!mymap.empty())
	{
		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
	}
}

void test_size_map(void)
{
	NAMESPACE::map<char, int> mymap;
	mymap['a'] = 101;
	mymap['b'] = 202;
	mymap['c'] = 302;

	std::cout << "mymap.size() is " << mymap.size() << '\n';
}

void test_max_size_map(void)
{
	int i;
	NAMESPACE::map<int, int> mymap;

	if (mymap.max_size() > 1000)
	{
		for (i = 0; i < 1000; i++)
			mymap[i] = 0;
		std::cout << "The map contains 1000 elements.\n";
	}
	else
		std::cout << "The map could not hold 1000 elements.\n";
}

void test_element_access_operator_map(void)
{
	NAMESPACE::map<char, std::string> mymap;

	mymap['a'] = "an element";
	mymap['b'] = "another element";
	mymap['c'] = mymap['b'];

	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

	std::cout << "mymap now contains " << mymap.size() << " elements.\n";
}

void test_insert_map(void)
{
	NAMESPACE::map<char, int> mymap;

	// first insert function version (single parameter):
	mymap.insert(NAMESPACE::pair<char, int>('a', 100));
	mymap.insert(NAMESPACE::pair<char, int>('z', 200));

	NAMESPACE::pair<NAMESPACE::map<char, int>::iterator, bool> ret;
	ret = mymap.insert(NAMESPACE::pair<char, int>('z', 500));
	if (ret.second == false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}
	
	// second insert function version (with hint position):
	NAMESPACE::map<char, int>::iterator it = mymap.begin();
	mymap.insert(it, NAMESPACE::pair<char, int>('b', 300)); // max efficiency inserting
	mymap.insert(it, NAMESPACE::pair<char, int>('c', 400)); // no max efficiency inserting
	std::cout << "size:\n"
			  << mymap.size() << '\n';
	
	// third insert function version (range insertion):
	NAMESPACE::map<char, int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));
	
	// showing contents:
	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it = anothermap.begin(); it != anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void test_erase_map(void)
{
	NAMESPACE::map<char, int> mymap;
	NAMESPACE::map<char, int>::iterator it;

	// insert some values:
	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	mymap['d'] = 40;
	mymap['e'] = 50;
	mymap['f'] = 60;

	it = mymap.find('b');
	mymap.erase(it); // erasing by iterator
	
	mymap.erase('c'); // erasing by key
	
	it = mymap.find('e');
	mymap.erase(it, mymap.end()); // erasing by range

	// show content:
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void test_swap_map(void)
{
	NAMESPACE::map<char, int> foo, bar;

	foo['x'] = 100;
	foo['y'] = 200;

	bar['a'] = 11;
	bar['b'] = 22;
	bar['c'] = 33;

	foo.swap(bar);

	std::cout << "foo contains:\n";
	for (NAMESPACE::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (NAMESPACE::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void test_clear_map(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;

	std::cout << "mymap contains:\n";
	for (NAMESPACE::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mymap.clear();
	mymap['a'] = 1101;
	mymap['b'] = 2202;

	std::cout << "mymap contains:\n";
	for (NAMESPACE::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void test_key_comp_map(void)
{
	NAMESPACE::map<char, int> mymap;

	NAMESPACE::map<char, int>::key_compare mycomp = mymap.key_comp();

	mymap['a'] = 100;
	mymap['b'] = 200;
	mymap['c'] = 300;

	std::cout << "mymap contains:\n";

	char highest = mymap.rbegin()->first; // key value of last element

	NAMESPACE::map<char, int>::iterator it = mymap.begin();
	do
	{
		std::cout << it->first << " => " << it->second << '\n';
	} while (mycomp((*it++).first, highest));
}

void test_value_comp_map(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['x'] = 1001;
	mymap['y'] = 2002;
	mymap['z'] = 3003;

	std::cout << "mymap contains:\n";

	NAMESPACE::pair<char, int> highest = *mymap.rbegin(); // last element

	NAMESPACE::map<char, int>::iterator it = mymap.begin();
	do
	{
		std::cout << it->first << " => " << it->second << '\n';
	} while (mymap.value_comp()(*it++, highest));
}

void test_find_map(void)
{
	NAMESPACE::map<char, int> mymap;
	NAMESPACE::map<char, int>::iterator it;

	mymap['a'] = 50;
	mymap['b'] = 100;
	mymap['c'] = 150;
	mymap['d'] = 200;

	it = mymap.find('b');
	if (it != mymap.end())
		mymap.erase(it);

	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymap.find('a')->second << '\n';
	std::cout << "c => " << mymap.find('c')->second << '\n';
	std::cout << "d => " << mymap.find('d')->second << '\n';
}

void test_count_map(void)
{
	NAMESPACE::map<char, int> mymap;
	char c;

	mymap['a'] = 101;
	mymap['c'] = 202;
	mymap['f'] = 303;

	for (c = 'a'; c < 'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c) > 0)
			std::cout << " is an element of mymap.\n";
		else
			std::cout << " is not an element of mymap.\n";
	}
}

void test_lower_upper_bound_map(void)
{
	NAMESPACE::map<char, int> mymap;
	NAMESPACE::map<char, int>::iterator itlow, itup;

	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;

	itlow = mymap.lower_bound('b'); // itlow points to b
	itup = mymap.upper_bound('d');	// itup points to e (not d!)

	mymap.erase(itlow, itup); // erases [itlow,itup)

	// print content:
	for (NAMESPACE::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}

void test_equal_range_map(void)
{
	NAMESPACE::map<char, int> mymap;

	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;

	NAMESPACE::pair<NAMESPACE::map<char, int>::iterator, NAMESPACE::map<char, int>::iterator> ret;
	ret = mymap.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

void test_get_allocator_map(void)
{
	int psize;
	NAMESPACE::map<char, int> mymap;
	NAMESPACE::pair<const char, int> *p;

	// allocate an array of 5 elements using mymap's allocator:
	p = mymap.get_allocator().allocate(5);

	// assign some values to array
	psize = sizeof(NAMESPACE::map<char, int>::value_type) * 5;

	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

	mymap.get_allocator().deallocate(p, 5);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//                                                                                  //
//                                     MAIN                                         //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void    test_stack()
{
    std::cout << std::endl << "<>----- Test empty -----<>" << std::endl;
    empty_test_stack();
    std::cout << std::endl << "<>----- Test size -----<>" << std::endl;
    size_test_stack();
    std::cout << std::endl << "<>----- Test top -----<>" << std::endl;
    top_test_stack();
    std::cout << std::endl << "<>----- Test push and pop -----<>" << std::endl;
    test_push_and_pop_stack();
}

void test_vector()
{
    std::cout << std::endl << "<>----- Test constructor -----<>" << std::endl;
    test_constructor_vector();
    std::cout << std::endl << "<>----- Test assignment operator -----<>" << std::endl;
    test_assignment_operator_vector();
    std::cout << std::endl << "<>----- Test begin -----<>" << std::endl;
    test_begin_vector();
    std::cout << std::endl << "<>----- Test end -----<>" << std::endl;
    test_end_vector();
    std::cout << std::endl << "<>----- Test rbegin -----<>" << std::endl;
    test_rbegin_vector();
    std::cout << std::endl << "<>----- Test rend -----<>" << std::endl;
    test_rend_vector();
    std::cout << std::endl << "<>----- Test size -----<>" << std::endl;
    test_size_vector();
    std::cout << std::endl << "<>----- Test max size -----<>" << std::endl;
    test_max_size_vector();
    std::cout << std::endl << "<>----- Test resize -----<>" << std::endl;
    test_resize_vector();
    std::cout << std::endl << "<>----- Test capacity -----<>" << std::endl;
    test_capacity_vector();
    std::cout << std::endl << "<>----- Test empty -----<>" << std::endl;
    test_empty_vector();
    std::cout << std::endl << "<>----- Test reserve -----<>" << std::endl;
    test_reserve_vector();
    std::cout << std::endl << "<>----- Test subscript operator -----<>" << std::endl;
    test_subscript_operator_vector();
    std::cout << std::endl << "<>----- Test at -----<>" << std::endl;
    test_at_vector();
    std::cout << std::endl << "<>----- Test front -----<>" << std::endl;
    test_front_vector();
    std::cout << std::endl << "<>----- Test back -----<>" << std::endl;
    test_back_vector();
    std::cout << std::endl << "<>----- Test assign -----<>" << std::endl;
    test_assign_vector();
    std::cout << std::endl << "<>----- Test push_back -----<>" << std::endl;
    //test_push_back_vector();
    std::cout << std::endl << "<>----- Test pop_back -----<>" << std::endl;
    test_pop_back_vector();
    std::cout << std::endl << "<>----- Test insert -----<>" << std::endl;
    test_insert_vector();
    std::cout << std::endl << "<>----- Test erase -----<>" << std::endl;
    test_erase_vector();
    std::cout << std::endl << "<>----- Test swap -----<>" << std::endl;
    test_swap_vector();
    std::cout << std::endl << "<>----- Test clear -----<>" << std::endl;
    test_clear_vector();
    std::cout << std::endl << "<>----- Test get_allocator -----<>" << std::endl;
    test_get_allocator_vector();
    std::cout << std::endl << "<>----- Test swap non_member -----<>" << std::endl;
    test_swap_non_member_vector();
    std::cout << std::endl << "<>----- Test enable_if and is_integral -----<>" << std::endl;
    test_enable_if_and_is_integral_vector();
    std::cout << std::endl << "<>----- Test reverse iterator relational operators -----<>" << std::endl;
    test_reverse_iterator_relational_operators_vector();
}

void test_map()
{
    std::cout << std::endl << "<>----- Test constructor -----<>" << std::endl;
	test_constructors_map();
    std::cout << std::endl << "<>----- Test assignment operator -----<>" << std::endl;
	test_assignment_operator_map();
    std::cout << std::endl << "<>----- Test begin/end -----<>" << std::endl;
	test_begin_end_map();
    std::cout << std::endl << "<>----- Test rbegin/rend -----<>" << std::endl;
	test_rbegin_rend_map();
    std::cout << std::endl << "<>----- Test empty -----<>" << std::endl;
	test_empty_map();
    std::cout << std::endl << "<>----- Test size -----<>" << std::endl;
	test_size_map();
    std::cout << std::endl << "<>----- Test max size -----<>" << std::endl;
	test_max_size_map();
    std::cout << std::endl << "<>----- Test element access operator -----<>" << std::endl;
	test_element_access_operator_map();
    std::cout << std::endl << "<>----- Test insert -----<>" << std::endl;
	test_insert_map();
    std::cout << std::endl << "<>----- Test erase -----<>" << std::endl;
	test_erase_map();
    std::cout << std::endl << "<>----- Test swap -----<>" << std::endl;
	test_swap_map();
    std::cout << std::endl << "<>----- Test clear -----<>" << std::endl;
	test_clear_map();
    std::cout << std::endl << "<>----- Test key_comp -----<>" << std::endl;
	test_key_comp_map();
    std::cout << std::endl << "<>----- Test value_comp -----<>" << std::endl;
	test_value_comp_map();
    std::cout << std::endl << "<>----- Test find -----<>" << std::endl;
	test_find_map();
    std::cout << std::endl << "<>----- Test count -----<>" << std::endl;
	test_count_map();
    std::cout << std::endl << "<>----- Test lower bound/upper bound -----<>" << std::endl;
	test_lower_upper_bound_map();
    std::cout << std::endl << "<>----- Test equal range -----<>" << std::endl;
	test_equal_range_map();
    std::cout << std::endl << "<>----- Test get_allocator -----<>" << std::endl;
	test_get_allocator_map();
}

int main()
{
    std::cout << "//////////////////////////////" << std::endl;
    std::cout << "//////// TESTS STACK /////////" << std::endl;
    std::cout << "//////////////////////////////" << std::endl;
    test_stack();

    std::cout << std::endl << "//////////////////////////////" << std::endl;
    std::cout << "//////// TESTS VECTOR ////////" << std::endl;
    std::cout << "//////////////////////////////" << std::endl;
    test_vector();

    std::cout << std::endl << "//////////////////////////////" << std::endl;
    std::cout << "////////// TESTS MAP /////////" << std::endl;
    std::cout << "//////////////////////////////" << std::endl;
    test_map();
    return (0);
}