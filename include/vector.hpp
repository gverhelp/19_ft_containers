#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include "utils/iterator.hpp"
# include "utils/utils.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            //------------------- Member types -------------------//
            typedef T                                                       value_type;
            typedef Alloc                                                   allocator_type;
            typedef typename allocator_type::reference                      reference;
            typedef typename allocator_type::const_reference                const_reference;
            typedef typename allocator_type::pointer                        pointer;
            typedef typename allocator_type::const_pointer                  const_pointer;
            typedef ft::It<value_type>                                      iterator;
            typedef ft::It<const value_type>                                const_iterator;
            typedef ft::reverse_iterator<iterator>                          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef size_t                                                  size_type;

            //------------------- Member functions : Constructors & Destructor + operator = -------------------//
            explicit vector(const allocator_type& alloc = allocator_type()): _size(0), _capacity(0), _base(alloc)
            {
                this->_ptr = this->_base.allocate(0);
            }
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _size(n), _capacity(n), _base(alloc)
            {
                this->_ptr = this->_base.allocate(n);
                for (size_t a = 0; a < n; a++)
                    this->_base.construct(this->_ptr + a, val);
            }
            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr): _size(0), _capacity(0), _base(alloc) //Range constructor
            {
                for (; first < last; first++)
                    this->_size++;
                this->_capacity = this->_size;
                first -= _size;
                this->_ptr = this->_base.allocate(this->_size);
                for (size_t a = 0; a < this->_size; a++)
                    this->_base.construct(_ptr + a, *(first + a));
            }

            vector(const vector& x): _size(x._size), _capacity(x._capacity), _base(x._base)
            {
                this->_ptr = this->_base.allocate(0);
                *this = x;
            }
            vector& operator=(const vector& x)
            {
                if (this != &x)
                {
                    this->clear();
                    this->_base.deallocate(this->_ptr, this->_capacity);
                    this->_ptr = this->_base.allocate(x._capacity);
                    for (size_t a = 0; a < x._size; a++)
                        this->_base.construct(this->_ptr + a, *(x._ptr + a));
                    this->_size = x._size;
                    this->_capacity = x._capacity;
                }
                return (*this);
            }
            virtual ~vector()
            {
                this->clear();
                this->_base.deallocate(this->_ptr, this->_capacity);
            }

            //------------------- Member functions : Iterators -------------------//
            iterator begin() { return (iterator(this->_ptr)); }
            const_iterator begin() const { return (const_iterator(this->_ptr)); }
            iterator end() { return (iterator(this->_ptr + this->_size)); }
            const_iterator end() const { return (const_iterator(this->_ptr + this->_size)); }
            reverse_iterator rbegin() { return (reverse_iterator(this->_ptr + this->_size)); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->_ptr + this->_size)); }
            reverse_iterator rend() { return (reverse_iterator(this->_ptr)); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(this->_ptr)); }

            //------------------- Member functions : Capacity -------------------//
            size_type size() const { return (this->_size); } //Return size
            size_type max_size() const { return (this->_base.max_size()); } //Return maximum size of allocated storage
            void resize(size_type n, value_type val = value_type())
            {
                if (n < this->_size)
                {
                    for (size_t a = n; a < this->_size; a++)
                        this->_base.destroy(this->_ptr + a);
                }
                else if (n > this->_size && n <= this->_capacity)
                {
                    for (size_t a = this->_size; a < n; a++)
                        this->_base.construct(this->_ptr + a, val);
                }
                else if (n > this->_size && n > this->_capacity)
                {
                    if (n < this->_capacity * 2)
                        reserve(this->_capacity * 2);
                    else
                        reserve(n);
                    for (size_t a = this->_size; a < n; a++)
                        this->_base.construct(this->_ptr + a, val);
                }
                this->_size = n;
            }
            size_type capacity() const { return (this->_capacity); } //Return maximum size 
            bool empty() const
            {
                if (this->_size == 0)
                    return (true);
                return (false);
            }
            void reserve(size_type n) //Request a change in capacity
            {
                if (n > this->_capacity)
                {
                    vector copy;

                    copy = *this;
                    this->clear();
                    this->_base.deallocate(this->_ptr, this->_capacity);
                    this->_ptr = this->_base.allocate(n);
                    for (size_t a = 0; a < copy._size; a++)
                        this->_base.construct(this->_ptr + a, *(copy._ptr + a));
                    this->_size = copy._size;
                    this->_capacity = n;
                }
            }

            //------------------- Member functions : Element access -------------------//
            reference operator[](size_type n) { return (at(n)); }
            const_reference operator[](size_type n) const { return (at(n)); } 
            reference at(size_type n)
            {
                if (n >= this->_size)
                    throw std::out_of_range("Vector"); 
                return (*(this->_ptr + n));
            }
            const_reference at(size_type n) const
            {
                if (n >= this->_size)
                    throw std::out_of_range("Vector"); 
                return *(this->_ptr + n);
            }
            reference front() { return (*this->_ptr); }
            const_reference front() const { return (*this->_ptr); }
            reference back() { return *(this->_ptr + this->_size - 1); }
            const_reference back() const { return *(this->_ptr + this->_size - 1); }

            //------------------- Member functions : Modifiers -------------------//
            template <class InputIterator>
            void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr) //Assign vector content
            {
                clear();
                insert(begin(), first, last);
                this->_capacity = _size;
            }
            void assign(size_type n, const value_type& val)
            {
                clear();
                for (size_t a = 0; a < n; a++)
                    push_back(val);
            }
            void push_back(const value_type& val) { resize(this->_size + 1, val); }
            void pop_back() { resize(this->_size - 1, value_type()); }
            iterator insert(iterator position, const value_type& val) //Insert elements
            {
                iterator it;
                size_t a = 0;
                size_t i = 0;

                for (it = this->begin(); it < position; it++)
                    a++;
                this->reserve(this->_size + 1);
                this->_size += 1;
                i = this->_size - 1;
                while (i > a)
                {
                    this->_ptr[i] = this->_ptr[i - 1];
                    i--;
                }
                this->_ptr[a] = val;
                return (begin() + a);
            }
            void insert(iterator position, size_type n, const value_type& val) //Insert elements
            {
                iterator it = position;
                for (size_t a = 0; a < n; a++)
                {
                    it = insert(it, val);
                    it++;
                }
            }
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr) //Insert elements
            {
                iterator    it = position;
                vector      tmp(first, last);
                iterator    begin = tmp.begin();
                iterator    end = tmp.end();
                
                for (; begin < end; begin++)
                {

                    it = insert(it, *begin);
                    it++;
                }
            }
            iterator erase(iterator position) //Erase element
            {
                iterator it;
                size_t a = 0;

                this->_size--;
                for (it = this->begin(); it < position; it++)
                    a++;
                for (; a < this->_size; a++)
                    this->_ptr[a] = this->_ptr[a + 1];
                if (position == this->end() + 1)
                    return (this->end());
                return (position);
            }
            iterator erase(iterator first, iterator last) //Erase elements
            {
                iterator it;
                size_t a = 0;
                size_t b = 0;
                size_t c = 0;

                for (it = this->begin(); it < first; it++)
                    a++;
                for (it = this->begin(); it < last; it++)
                    b++;
                c = b - a;
                this->_size -= c;
                for (; a < this->_size; a++)
                    this->_ptr[a] = this->_ptr[a + c];
                return (last - c);
            }
            void swap(vector& x)
            {
                pointer tmp;
                size_t  tmp2;
                size_t  tmp3;

                tmp = this->_ptr;
                tmp2 = this->_size;
                tmp3 = this->_capacity;
                this->_ptr = x._ptr;
                this->_size = x._size;
                this->_capacity = x._capacity;
                x._ptr = tmp;
                x._size = tmp2;
                x._capacity = tmp3;
            }
            void clear()
            {
                for (size_t a = 0; a < this->_size; a++)
                    this->_base.destroy(&this->_ptr[a]);
                this->_size = 0;
            }

            //------------------- Member functions : Allocator -------------------//
            allocator_type get_allocator() const { return (this->_base); }

        private:
            size_type       _size;
            size_type       _capacity;
            allocator_type  _base;
            pointer         _ptr;
    };

    //------------------- Non-member functions -------------------//
    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs)); }
    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs)); }
    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }
    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }
    template <class T, class Alloc>
    void swap (vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }
}

#endif
