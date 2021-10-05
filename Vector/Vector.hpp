#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iterator> //Remplacer par iterator.hpp

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            ///// Member types /////
            typedef T                                       value_type;
            typedef Alloc                                   allocator_type;
            typedef value_type&                             reference;
            typedef const value_type&                       const_reference;
            typedef value_type*                             pointer;
            typedef const value_type*                       const_pointer;
            typedef std::iterator<value_type>               iterator;
            typedef const std::iterator<value_type>         const_iterator;
            typedef std::reverse_iterator<iterator>         reverse_iterator;
            typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;
            typedef unsigned long long                      difference_type;
            typedef size_t                                  size_type;

            ///// Member functions : Constructors & Destructor + operator = /////
            explicit vector(const allocator_type& alloc = allocator_type()) //Default constructor
            {
                ///////////
            };
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) //Fill constructor
            {
                ///////////
            };
            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) //Range constructor
            {
                ///////////
            };
            vector(const vector& x) //Copy constructor
            {
                ///////////
            };
            vector& operator=(const vector& x)
            {
                if (this != &x)
                {
                    //////////
                }
                return (*this);
            };
            virtual ~vector() // Destructor
            {
                ///////////
            };

            ///// Member functions : Iterators /////
            iterator begin() {}; //Return iterator to beginning
            const_iterator begin() const {}; //Return iterator to beginning
            iterator end() {}; //Return iterator to end
            const_iterator end() const {}; //Return iterator to end
            reverse_iterator rbegin() {}; //Return reverse iterator to reverse beginning
            const_reverse_iterator rbegin() const {}; //Return reverse iterator to reverse beginning
            reverse_iterator rend() {}; //Return reverse iterator to reverse end
            const_reverse_iterator rend() const {}; //Return reverse iterator to reverse end

            ///// Member functions : Capacity /////
            size_type size() const {}; //Return size
            size_type max_size() const {}; //Return maximum size
            void resize(size_type n, value_type val = value_type()) {}; //Change size
            size_type capacity() const {}; //Return size of allocated storage capacity
            bool empty() const {}; //Test whether vector is empty 
            void reserve(size_type n) {}; //Request a change in capacity

            ///// Member functions : Element access /////
            reference operator[](size_type n) {}; //Access element
            const_reverse operator[](size_type n) const {} //Access element
            reference at(size_type n) {}; //Access element
            const_reference at(size_type n) const {}; //Access element
            reference front() {}; //Access first element
            const_reference front() const {}; //Access first element
            reference back() {}; //Access last element
            const_reference back() const {}; //Access last element

            ///// Member functions : Modifiers /////
            template <class InputIterator>
            void assign(InputIterator first, InputIterator last) {}; //Assign vector content 
            void assign(size_type n, const value_type& val) {}; //Assign vector content 
            void push_back(const value_type& val) {}; //Add element at the end
            void pop_back() {}; //Delete last element
            iterator insert(iterator position, const value_type& val) {}; //Insert elements
            void insert(iterator position, size_type n, const value_type& val) {}; //Insert elements
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last) {}; //Insert elements
            iterator erase(iterator position) {}; //Erase elements 
            iterator erase(iterator first, iterator last) {}; //Erase elements 
            void swap(vector& x) {}; //Swap content
            void clear() {}; //Clear content 

            ///// Member functions : Allocator /////
            allocator_type get_allocator() const {}; //Get allocator

        private:
            size_type _size;
            size_type _maxSize;
    };

    ///// Non-member function overloads /////
    //Check le return sur cppref (Relational operators for vector)
    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {};
    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {};
    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {};
    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {};
    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {};
    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {};

    template <class T, class Alloc>
    void swap (vector<T, Alloc>& x, vector<T, Alloc>& y) {};
}

#endif