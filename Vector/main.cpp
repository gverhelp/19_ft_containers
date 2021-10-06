#include "vector.hpp"
#include <vector>
#include <iostream>

int main()
{
    ft::vector<int> v1;
    std::vector<int> v2;

    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.resize(3, -7);
    for (size_t a = 0; a < 4; a++)
        std::cout << "(v1) Element " << a << " : " << v1[a] << std::endl;     ///// v1[a] throw an exception at 4 but is it correct?
    std::cout << "(v1) Size : " << v1.size() << std::endl << std::endl;

    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
    v2.push_back(4);
    v2.resize(3, -7);
    for (size_t a = 0; a < 4; a++)
        std::cout << "(v2) Element " << a << " : " << v2[a] << std::endl;
    std::cout << "(v2) Size : " << v2.size() << std::endl;
    return (0);
}