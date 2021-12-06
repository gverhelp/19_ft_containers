#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include <iostream>

namespace ft
{
    template < class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            //------------------- Member types -------------------//
            typedef T           value_type;
            typedef Container   container_type;
            typedef size_t      size_type;

            //------------------- Member functions -------------------//
            explicit stack(const container_type& ctnr = container_type()): c(ctnr) {}
            virtual ~stack() {}
            stack& operator=(const stack& copy)
            {
                if (this != &copy)
                    this->c = copy.c;
                return (*this);
            }
            value_type& top() { return (this->c.back()); }
            const value_type& top() const { return (this->c.back()); }
            bool empty() const { return (this->c.empty()); }
            size_type size() const { return (this->c.size()); }
            void push(const value_type& val) { this->c.push_back(val); }
            void pop() { this->c.pop_back(); }

        private:
            //------------------- Non member function : relational operators -------------------//
            friend bool operator==(const stack& lhs, const stack& rhs) { return (lhs.c == rhs.c); }
            friend bool operator!=(const stack& lhs, const stack& rhs) { return (lhs.c != rhs.c); }
            friend bool operator<(const stack& lhs, const stack& rhs) { return (lhs.c < rhs.c); }
            friend bool operator<=(const stack& lhs, const stack& rhs) { return (lhs.c <= rhs.c); }
            friend bool operator>(const stack& lhs, const stack& rhs) { return (lhs.c > rhs.c); }
            friend bool operator>=(const stack& lhs, const stack& rhs) { return (lhs.c >= rhs.c); }

        protected:
            //------------------- Member object -------------------//
            container_type c;
    };
}

#endif