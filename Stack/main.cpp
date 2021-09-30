#include "./stack.hpp"
#include <vector>
#include <stack>

int main()
{
    ft::stack<int> stack;

    std::cout << "Stack size : " << stack.size() << std::endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    std::cout << "Stack size : " << stack.size() << std::endl;
    stack.pop();
    std::cout << "Stack size : " << stack.size() << std::endl;

    ft::stack<int> stack2(stack);

    while (!stack.empty())
    {
        std::cout << ' ' << stack.top();
        stack.pop();
    }
    std::cout << "\nStack size : " << stack.size() << std::endl;

    while (!stack2.empty())
    {
        std::cout << ' ' << stack2.top();
        stack2.pop();
    }
    std::cout << "\nStack size : " << stack2.size() << std::endl;

    return (0);
}