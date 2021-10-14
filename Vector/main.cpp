#include "vector.hpp"
#include <iostream>
#include <vector>

int main()
{
    ft::vector<int> v1;
    ft::vector<int>::iterator it;
    ft::vector<int>::reverse_iterator rit;
    int a = 0;

    std::cout << std::endl << "//-------------------- Default constructor / push_back / resize / front / back --------------------//" << std::endl;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.resize(5, -7);
    for (size_t a = 0; a < v1.size(); a++)
        std::cout << "(v1) Element " << a << " : " << v1[a] << std::endl;     ///// v1[a] throw an exception when I print an out of range element, but is it correct?
    std::cout << "(v1) Front : " << v1.front() << std::endl;
    std::cout << "(v1) Back : " << v1.back() << std::endl;
    std::cout << "(v1) Size : " << v1.size() << std::endl << std::endl;


    std::cout << "//-------------------- Copy constructor --------------------//" << std::endl;
    ft::vector<int> v2(v1);

    for (size_t a = 0; a < v2.size(); a++)
        std::cout << "(v2) Element " << a << " : " << v2[a] << std::endl;
    std::cout << "(v2) Size : " << v2.size() << std::endl << std::endl;
    v1.clear();

    std::cout << "//-------------------- Swap / Assign --------------------//" << std::endl;
    v1.assign(4, 25);
    v2.assign(5, 42);
//    v2.assign(v2.begin() + 1, v2.end() - 1);
    v1.swap(v2);
    for (size_t a = 0; a < v1.size(); a++)
        std::cout << "(v1) Element " << a << " : " << v1[a] << std::endl;
    std::cout << "(v1) Size : " << v1.size() << std::endl << std::endl;
    for (size_t a = 0; a < v2.size(); a++)
        std::cout << "(v2) Element " << a << " : " << v2[a] << std::endl;
    std::cout << "(v2) Size : " << v2.size() << std::endl;
    v1.clear();
    v2.clear();

    std::cout << "//-------------------- Iterator : begin / end --------------------//" << std::endl;
    v2.assign(5, 0);
    for (it = v2.begin(); it != v2.end(); it++)
        *it = a++;
    a = 0;
    for (it = v2.begin(); it != v2.end(); it++)
        std::cout << "(v2) Element " << a++ << " : " << *it << std::endl;
    std::cout << "(v2) Size : " << v2.size() << std::endl;
    a = 0;

    std::cout << "//-------------------- Iterator : rbegin / rend --------------------//" << std::endl;
    v1.push_back(3);
    v1.push_back(14);
    v1.push_back(20);
    v1.push_back(37);
    for (rit = v1.rbegin(); rit != v1.rend(); rit++)
        std::cout << "(v1) Element " << a++ << " : " << *rit << std::endl;
    std::cout << "(v1) Size : " << v1.size() << std::endl;
    v1.clear();
    a = 0;

    return (0);
}