#include "vector.hpp"
#include <vector>
#include <iostream>

int main()
{
    ft::vector<int> v1;

    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.resize(3, -7);
    for (size_t a = 0; a < v1.size(); a++)
        std::cout << "(v1) Element " << a << " : " << v1[a] << std::endl;     ///// v1[a] throw an exception when I print an out of range element, but is it correct?
    std::cout << "(v1) Size : " << v1.size() << std::endl << std::endl;
/*
    ft::vector<int> v2(v1);                                                   ///// Not working, freed

    for (size_t a = 0; a < v2.size(); a++)
        std::cout << "(v2) Element " << a << " : " << v2[a] << std::endl;
    std::cout << "(v2) Size : " << v2.size() << std::endl << std::endl;
*/

/*
    std::cout << "//---------- Swap ----------//" << std::endl;
    v1.swap(v2);
    for (size_t a = 0; a < v1.size(); a++)
        std::cout << "(v1) Element " << a << " : " << v1[a] << std::endl;
    std::cout << "(v1) Size : " << v1.size() << std::endl << std::endl;
    for (size_t a = 0; a < v2.size(); a++)
        std::cout << "(v2) Element " << a << " : " << v2[a] << std::endl;
    std::cout << "(v2) Size : " << v2.size() << std::endl;
*/
    return (0);
}


/*
    v2.push_back(5);
    v2.push_back(6);
    v2.push_back(7);
    v2.push_back(8);
    v2.resize(3, -7);
    for (size_t a = 0; a < v2.size(); a++)
        std::cout << "(v2) Element " << a << " : " << v2[a] << std::endl;
    std::cout << "(v2) Size : " << v2.size() << std::endl << std::endl;
*/