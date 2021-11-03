#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include <utility>
# include "utils/utils.hpp"
# include "utils/rbtree.hpp"

namespace ft
{
    template < class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
            typedef Key                                 key_type;
            typedef T                                   mapped_type;
            typedef ft::pair<const Key, T>              value_type;
            typedef size_t                              size_type;
            typedef ptrdiff_t                           difference_type;
            typedef Compare                             key_compare;
            typedef Allocator                           allocator_type;
            typedef value_type&                         reference;
            typedef const value_type&                   const_reference;
            typedef typename Allocator::pointer         pointer;
            typedef typename Allocator::const_pointer   const_pointer;
            //typedef "LegacyBidirectionalIterator to value_type" iterator;
            //typedef "LegacyBidirectionalIterator to const value_type" const_iterator;
            //typedef std::reverse_iterator<iterator> reverse_iterator;
            //typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

            //------------------- Member functions : Constructor / Destructor + operator = -------------------//
            //explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {}
            //template <class InputIterator>
            //map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {}
            //map (const map& x) {}
            //~map() {}

            //map& operator= (const map& x) {}

            //------------------- Member functions : Iterators -------------------//
            //iterator begin() {}
            //const_iterator begin() const {}
            //iterator end() {}
            //const_iterator end() const {}
            //reverse_iterator rbegin() {}
            //const_reverse_iterator rbegin() const {}
            //reverse_iterator rend() {}
            //const_reverse_iterator rend() const {}

            //------------------- Member functions : Capacity -------------------//
            bool empty() const
            {
                if (this->_size == 0)
                    return (true);
                return (false);
            }
            size_type size() const { return (this->_size); }
            size_type max_size() const { return (this->_alloc.max_size()); }

            //------------------- Member functions : Element access -------------------//
            //mapped_type& operator[] (const key_type& k) {}

            //------------------- Member functions : Modifiers -------------------//	
            //pair<iterator,bool> insert (const value_type& val) {}
            //iterator insert (iterator position, const value_type& val) {}	
            //template <class InputIterator>
            //void insert (InputIterator first, InputIterator last) {}

            //void erase (iterator position) {}	
            //size_type erase (const key_type& k) {}
            //void erase (iterator first, iterator last) {}

            //void swap (map& x) {}

            //void clear() {}

            //------------------- Member functions : Observers -------------------//
            //key_compare key_comp() const {}
            //value_compare value_comp() const {}

            //------------------- Member functions : Operations -------------------//
            //iterator find (const key_type& k) {}
            //const_iterator find (const key_type& k) const {}

            //size_type count (const key_type& k) const {}

            //iterator lower_bound (const key_type& k) {}
            //const_iterator lower_bound (const key_type& k) const {}

            //iterator upper_bound (const key_type& k) {}
            //const_iterator upper_bound (const key_type& k) const {}

            //pair<const_iterator,const_iterator> equal_range (const key_type& k) const {}
            //pair<iterator,iterator>             equal_range (const key_type& k) {}

            //------------------- Member functions : Allocator -------------------//
            allocator_type get_allocator() const { return (this->_alloc); }

        private:
            allocator_type  _alloc;
            key_compare     _comp;
            RBTree          _tree;
            size_type       _size;

    };
}

#endif