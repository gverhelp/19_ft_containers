#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <iostream>
# include "utils.hpp"

namespace ft
{
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_acces_iterator_tag : public bidirectional_iterator_tag {};

    template < class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
    struct iterator
    {
        //------------------- Member types -------------------//
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };

    template < class Iterator >
    struct iterator_traits
    {
        //------------------- Member types -------------------//
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template < class T >
    struct iterator_traits<T*>
    {
        //------------------- Member types -------------------//
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template < class T >
    struct iterator_traits<const T*>
    {
        //------------------- Member types -------------------//
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    /////////////////////////////////////////////////////////////////////
    //////////////////// Iterator : Reverse iterator ////////////////////
    /////////////////////////////////////////////////////////////////////
    template < class Iterator >
    class reverse_iterator
    {
        public:
            //------------------- Member types -------------------//
            typedef Iterator                                                    iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
            typedef typename ft::iterator_traits<Iterator>::reference           reference;

            //------------------- Member functions : Constructors + operator = -------------------//
            reverse_iterator(): current() {}
            explicit reverse_iterator(iterator_type x): current(x) {}
            template < class U >
            reverse_iterator(const reverse_iterator<U>& other): current(other.base()) {}
            template < class U >
            reverse_iterator& operator=(const reverse_iterator<U>& other)
            {
                if (this != &other)
                    this->current = other.current;
                return (*this);
            }

            //------------------- Member functions -------------------//
            reference operator*() const { Iterator tmp = this->current; return *--tmp; }
            pointer operator->() const { return &(reverse_iterator::operator*()); }
            reference operator[](difference_type n) const { return (this->base()[-n-1]); }
            iterator_type base() const { return (Iterator(this->current)); }
            reverse_iterator& operator++() { this->current--; return (*this); }
            reverse_iterator& operator--() { this->current++; return (*this); }
            reverse_iterator operator++(int) { reverse_iterator temp = *this; this->current--; return temp; }
            reverse_iterator operator--(int) { reverse_iterator temp = *this; this->current++; return temp; }
            reverse_iterator operator+(difference_type n) const { return reverse_iterator(current - n); }
            reverse_iterator operator-(difference_type n) const { return reverse_iterator(current + n); }
            reverse_iterator& operator+=(difference_type n) { this->current -= n; return (*this); }
            reverse_iterator& operator-=(difference_type n) { this->current += n; return (*this); }

        protected:
            iterator_type current;
    };

    //------------------- Reverse iterator : non-member functions -------------------//
    template < class Iterator >
    bool operator==(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }
    template < class Iterator, class Iterator2 >
    bool operator==(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return (lhs.base() == rhs.base()); }
    template < class Iterator >
    bool operator!=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }
    template < class Iterator, class Iterator2 >
    bool operator!=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return (lhs.base() != rhs.base()); }
    template < class Iterator >
    bool operator<(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }
    template < class Iterator, class Iterator2 >
    bool operator<(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return (lhs.base() > rhs.base()); }
    template < class Iterator >
    bool operator<=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }
    template < class Iterator, class Iterator2 >
    bool operator<=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return (lhs.base() >= rhs.base()); }
    template < class Iterator >
    bool operator>(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }
    template < class Iterator, class Iterator2 >
    bool operator>(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return (lhs.base() < rhs.base()); }
    template < class Iterator >
    bool operator>=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }
    template < class Iterator, class Iterator2 >
    bool operator>=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator2>& rhs) { return (lhs.base() <= rhs.base()); }
    template < class Iterator >
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) { return (reverse_iterator<Iterator>(it.base() - n)); }
    template < class Iterator >
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (rhs.base() - lhs.base()); }
    template < class Iterator, class Iterator2 >
    typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator2>& rhs) { return (rhs.base() - lhs.base()); }
    
    ///////////////////////////////////////////////////////////
    //////////////////// Iterator : Vector ////////////////////
    ///////////////////////////////////////////////////////////
    template < class T >
    class It
    {
        public:
            //------------------- Member types -------------------//
            typedef typename ft::iterator_traits<T*>::iterator_category   iterator_category;
            typedef typename ft::iterator_traits<T*>::value_type          value_type;
            typedef typename ft::iterator_traits<T*>::difference_type     difference_type;
            typedef typename ft::iterator_traits<T*>::pointer             pointer;
            typedef typename ft::iterator_traits<T*>::reference           reference;

            operator It< const T >() const { return (It< const T>(this->_node)); } // https://stackoverflow.com/questions/25117970/conversion-operator-with-const

            //------------------- Member functions : Constructors / Destructor -------------------//
            It(pointer ptr = nullptr): _node(ptr) {}
            It(const It& cpy): _node(cpy.base()) {}
            ~It() { _node = nullptr; }
            template < class U >
            It& operator=(const It<U>& copy)
            {
                if (this != &copy)
                    this->_node = copy._node;
                return (*this);
            } 

            //------------------- Member functions -------------------//
            reference operator*() const { return (*this->_node); }
            pointer operator->() const { return (this->_node); }
            It& operator++() { this->_node++; return (*this); }
            It operator++(int) { It tmp = *this; ++(*this); return (tmp); }
            It& operator+=(difference_type n) { this->_node += n; return (*this); }
            It operator+(difference_type n) const { It tmp = *this; return (tmp += n); }
            It& operator-=(difference_type n) { this->_node -= n; return (*this); }
            It operator-(difference_type n) const { It tmp = *this; return (tmp -= n); }
            It& operator--() { this->_node--; return (*this); }
            It  operator--(int) { It tmp = *this; --(*this); return (tmp); }
            reference operator[](difference_type n) const { return *(this->_node + n); }

            pointer base() const { return (this->_node); }

        private:
            pointer _node;
    };

    //-------------------- It non-member functions --------------------//
    template < class T >
    bool operator==(const ft::It<T>& lhs, const ft::It<T>& rhs) { return (lhs.base() == rhs.base()); }
    template < class T, class T2 >
    bool operator==(const ft::It<T>& lhs, const ft::It<T2>& rhs) { return (lhs.base() == rhs.base()); }
    template < class T >
    bool operator!=(const ft::It<T>& lhs, const ft::It<T>& rhs) { return (lhs.base() != rhs.base()); }
    template < class T, class T2 >
    bool operator!=(const ft::It<T>& lhs, const ft::It<T2>& rhs) { return (lhs.base() != rhs.base()); }
    template < class T >
    bool operator<(const ft::It<T>& lhs, const ft::It<T>& rhs) { return (lhs.base() < rhs.base()); }
    template < class T, class T2 >
    bool operator<(const ft::It<T>& lhs, const ft::It<T2>& rhs) { return (lhs.base() < rhs.base()); }
    template < class T >
    bool operator<=(const ft::It<T>& lhs, const ft::It<T>& rhs) { return (lhs.base() <= rhs.base()); }
    template < class T, class T2 >
    bool operator<=(const ft::It<T>& lhs, const ft::It<T2>& rhs) { return (lhs.base() <= rhs.base()); }
    template < class T >
    bool operator>(const ft::It<T>& lhs, const ft::It<T>& rhs) { return (lhs.base() > rhs.base()); }
    template < class T, class T2 >
    bool operator>(const ft::It<T>& lhs, const ft::It<T2>& rhs) { return (lhs.base() > rhs.base()); }
    template < class T >
    bool operator>=(const ft::It<T>& lhs, const ft::It<T>& rhs) { return (lhs.base() >= rhs.base()); }
    template < class T, class T2 >
    bool operator>=(const ft::It<T>& lhs, const ft::It<T2>& rhs) { return (lhs.base() >= rhs.base()); }
    template < class T >
    It<T> operator+(typename ft::It<T>::difference_type n, const ft::It<T>& it) { return (It<T>(it.base() + n)); }
    template < class T >
    typename ft::It<T>::difference_type operator-(const It<T>& lhs, const ft::It<T>& rhs) { return (lhs.base() - rhs.base()); }
    template < class T, class T2 >
    typename ft::It<T>::difference_type operator-(const It<T>& lhs, const ft::It<T2>& rhs) { return (lhs.base() - rhs.base()); }  /// iterator - const_itrator

    ////////////////////////////////////////////////////////
    //////////////////// Iterator : Map ////////////////////
    ////////////////////////////////////////////////////////
    template < typename T >
    class Itmap 
    {

        public:
            // ------------------- Member types ------------------- //
            typedef typename ft::iterator_traits< ft::iterator<ft::bidirectional_iterator_tag, T> >::iterator_category      iterator_category;
            typedef typename ft::iterator_traits< ft::iterator<ft::bidirectional_iterator_tag, T> >::value_type             value_type;
            typedef typename ft::iterator_traits< ft::iterator<ft::bidirectional_iterator_tag, T> >::difference_type        difference_type;
            typedef typename ft::iterator_traits< ft::iterator<ft::bidirectional_iterator_tag, T> >::pointer                pointer;
            typedef typename ft::iterator_traits< ft::iterator<ft::bidirectional_iterator_tag, T> >::reference              reference;
            typedef ft::Node<T>                                                                                             node_reference;
            typedef ft::Node<T>*                                                                                            node_pointer;

            operator Itmap< const T >() const { return (Itmap< const T>(this->_node)); }

			Itmap() : _node(u_nullptr), _end(u_nullptr) {}
            Itmap(node_pointer node, node_pointer end ): _node(node), _end(end) {}
            template < class U >
            Itmap(const Itmap<U>& cpy): _node(cpy._node), _end(cpy._end) {}
            ~Itmap() {}
            template < class U >
            Itmap& operator=(const Itmap<U>& copy)
            {
                if (this != &copy)
				{
                    this->_node = copy._node;
					this->_end = copy._end;
					this->_comp = copy._comp;
				}
                return (*this);
            }

            // ------------------- Member functions ------------------- //
            reference operator*() const { return (this->_node->data); }
            pointer operator->() const { return (&this->_node->data); }
            node_pointer base() const { return (this->_node); }
/*
            Itmap& operator++()
            {
				node_pointer    tmp;
				node_pointer    root;

				root = this->_node;
				while (root->parent != nullptr)
					root = root->parent;

				tmp = this->_node;
				while (tmp != nullptr && (tmp->right == nullptr || (tmp->parent != nullptr && tmp == tmp->parent->right)))
					tmp = tmp->parent;
				if (tmp && tmp->parent == root)
					tmp = root;
				if (tmp == nullptr)
					this->_node++;
				else
				{
					this->_node = tmp->right;
					while (this->_node != 0)
					{
						tmp = this->_node;
						this->_node = this->_node->left;
					}
					this->_node = tmp;
				}
				return (*this);

			}
*/
			Itmap& operator++(void)
			{
				node_pointer cursor = _node;
				
				if (_node->right == _end)
				{
					cursor = _node->parent;
					while (cursor != u_nullptr && cursor != _end
						&& cursor->data.first < _node->data.first)
						cursor = cursor->parent;
					if (cursor == 0)
						_node = _end;
					else
						_node = cursor;
				}
				else if (cursor == _end)
				{
					_node = _end;
				}
				else
				{
					cursor = _node->right;
					if (cursor == _end->parent
						&& cursor->right == _end)
					{
						_node = cursor;
					}
					else
					{
						while (cursor->left != _end)
							cursor = cursor->left;
					}
					_node = cursor;
				}
				return (*this);
			}

            Itmap operator++(int) 
            {
                Itmap tmp(*this);

                operator++();
                return (tmp);
            }

			Itmap& operator--(void)
			{
				node_pointer cursor = _node;
               	
				if (_node->left == _end)
				{
					cursor = _node->parent;
					while (cursor != u_nullptr && cursor != _end
						&& cursor->data.first > _node->data.first)
					{
						cursor = cursor->parent;
					}
					_node = cursor;
					if (cursor == 0)
						_node = _end->right;
					else
						_node = cursor;

				}
				else if (cursor == _end)
					_node = _end->right;
				else
				{
					cursor = _node->left;
					if (cursor == _end->parent
						&& cursor->left == _end)
						_node = cursor;
					else
					{
						while (cursor->right != _end)
						{
							cursor = cursor->right;
						}
					}
					_node = cursor;
				}
				return (*this);
			}

            Itmap operator--(int)
            {
                Itmap tmp(*this);

                operator--();
                return (tmp);
            }
        private :
            node_pointer 	_node;
			node_pointer	_end;
			
    };

    //-------------------- Itmap non-member functions --------------------//
    template < class T >
    bool operator==(const ft::Itmap<T>& lhs, const ft::Itmap<T>& rhs) { return (lhs.base() == rhs.base()); }
    template < class T, class T2 >
    bool operator==(const ft::Itmap<T>& lhs, const ft::Itmap<T2>& rhs) { return (lhs.base() == rhs.base()); }
    template < class T >
    bool operator!=(const ft::Itmap<T>& lhs, const ft::Itmap<T>& rhs) { return (lhs.base() != rhs.base()); }
    template < class T, class T2 >
    bool operator!=(const ft::Itmap<T>& lhs, const ft::Itmap<T2>& rhs) { return (lhs.base() != rhs.base()); }
	/*
    template < class T >
    bool operator<(const ft::Itmap<T>& lhs, const ft::Itmap<T>& rhs) { return (lhs->first < rhs->first); }
    template < class T, class T2 >
    bool operator<(const ft::Itmap<T>& lhs, const ft::Itmap<T2>& rhs) { return (lhs->first < rhs->first); }
    template < class T >
    bool operator<=(const ft::Itmap<T>& lhs, const ft::Itmap<T>& rhs) { return (lhs->first <= rhs->first); }
    template < class T, class T2 >
    bool operator<=(const ft::Itmap<T>& lhs, const ft::Itmap<T2>& rhs) { return (lhs->first <= rhs->first); }
    template < class T >
    bool operator>(const ft::Itmap<T>& lhs, const ft::Itmap<T>& rhs) { return (lhs->first > rhs->first); }
    template < class T, class T2 >
    bool operator>(const ft::Itmap<T>& lhs, const ft::Itmap<T2>& rhs) { return (lhs->first > rhs->first); }
    template < class T >
    bool operator>=(const ft::Itmap<T>& lhs, const ft::Itmap<T>& rhs) { return (lhs->first >= rhs->first); }
    template < class T, class T2 >
    bool operator>=(const ft::Itmap<T>& lhs, const ft::Itmap<T2>& rhs) { return (lhs->first >= rhs->first); }
	*/
}

#endif
