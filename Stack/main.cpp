#include "Stack.hpp"

int main()
{
    Stack<int> stack;

    std::cout << "Stack size : " << stack.size() << std::endl;
    stack.push(10);
    stack.push(20);
    std::cout << "Stack size : " << stack.size() << std::endl;

    return (0);
}