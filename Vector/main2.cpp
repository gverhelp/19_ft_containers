#include "vector.hpp"
#include <iostream>
#include <vector>

template < class T >
void print_container(T& c, std::string str)
{
    typename T::iterator it;

    std::cout << "Container " << str << " : ";
    for (it = c.begin(); it < c.end(); it++)
        std::cout << "[" << *it << "] ";
    std::cout << std::endl << "Size " << str << " : " << c.size() << std::endl;
}

int main()
{
    ft::vector<int> v1;

    for (size_t a = 0; a < 15; a++)
        v1.push_back(a);
    ft::vector<int> v2(v1.begin() + 1, v1.end());
    print_container(v1, "v1");
    print_container(v2, "v2");
    v1.insert(v1.begin() + 4, v2.begin(), v2.end());
    print_container(v1, "v1");
    print_container(v2, "v2");
    ft::vector<int> v3(5, 5);
    v1.assign(v3.begin(), v3.end());
    print_container(v1, "v1");
    print_container(v3, "v3");
    return (0);
}

