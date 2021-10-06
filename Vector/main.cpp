#include "vector.hpp"
#include <vector>
#include <iostream>

int main()
{
    ft::vector<int> v1(9);
    std::vector<int> v2(9);
    v1.reserve(8);
    v2.reserve(8);
    return (0);
}