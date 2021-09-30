#ifndef STACK_HPP
# define STACK_HPP

# include <deque>
# include <iostream>

namespace ft
{
    template < class T, class Container = std::deque<T> >
    class stack
    {
        public:
            ///// Member types /////
            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type;

            ///// Member functions /////
            explicit stack(const container_type& ctnr = container_type()): C(ctnr) {}
            virtual ~stack() {}
            stack& operator=(const stack& copy)
            {
                if (this != &copy)
                {
                    this->C = copy.C;
                }
                return (*this);
            }
            value_type& top()
            {
                return (this->C.back());
            }
            const value_type& top() const
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

        private:
            ///// Non member function : relational operators /////
            friend bool operator==(const stack& lhs, const stack& rhs)
            {
                return (lhs.C == rhs.C);
            }
            friend bool operator!=(const stack& lhs, const stack& rhs)
            {
                return (lhs.C != rhs.C);
            }
            friend bool operator<(const stack& lhs, const stack& rhs)
            {
                return (lhs.C < rhs.C);
            }
            friend bool operator<=(const stack& lhs, const stack& rhs)
            {
                return (lhs.C <= rhs.C);
            }
            friend bool operator>(const stack& lhs, const stack& rhs)
            {
                return (lhs.C > rhs.C);
            }
            friend bool operator>=(const stack& lhs, const stack& rhs)
            {
                return (lhs.C >= rhs.C);
            }

        protected:
                ///// Member object /////
                container_type C;
    };
}

#endif