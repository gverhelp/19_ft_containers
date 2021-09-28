#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <deque>

template<class T, class Container = std::deque<T>>
class Stack
{
    public:
        ///// Member types /////
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef Container container_type;
        typedef size_t size_type;

        ///// Member functions /////
        explicit Stack(const container_type& ctnr = container_type()): C(ctnr) {}
        virtual ~Stack();
        Stack& operator=(const Stack& copy)
        {
            if (this != &copy)
            {
                this->C = copy.C;
            }
            return (*this);
        }
    
        reference top()
        {
            return (this->C.back());
        }

        const_reference top()
        {
            return (this->C.back());
        }

        bool empty() const
        {
            return (this->C.empty());
        }

        size_type size() const
        {
            return (this->C.size());
        }

        void push(const value_type& val)
        {
            this->C.push_back(val);
        }

        void pop()
        {
            this->C.pop_back();
        }

        ///// Non member function : relational operators /////
        template< class T, class Container >
        bool operator==(const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs)
        {
            return (lhs.C == rhs.C);
        }

        template< class T, class Container >
        bool operator!=(const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs)
        {
            return (lhs.C != rhs.C);
        }
	
        template< class T, class Container >
        bool operator<(const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs)
        {
            return (lhs.C < rhs.C);
        }
	
        template< class T, class Container >
        bool operator<=(const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs)
        {
            return (lhs.C <= rhs.C);
        }

        template< class T, class Container >
        bool operator>(const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs)
        {
            return (lhs.C > rhs.C);
        }

        template< class T, class Container >
        bool operator>=(const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs)
        {
            return (lhs.C >= rhs.C);
        }

    private:
        ///// Member object /////
        container_type C;
};

#endif