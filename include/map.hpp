/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:43:00 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/11/29 13:34:16 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include <utility>
# include <iostream>
# include "utils/utils.hpp"
# include "utils/BTree.hpp"
# include "utils/iterator.hpp"

namespace ft
{
    template < class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >    /// Faire un rebind d'allocator
    class map
    {
        public:
            typedef Key                                     key_type;
            typedef T                                       mapped_type;
            typedef ft::pair<const key_type, mapped_type>   value_type;
            typedef size_t                                  size_type;
            typedef ptrdiff_t                               difference_type;
            typedef Compare                                 key_compare;
            typedef Allocator      							allocator_type;
            typedef value_type&                             reference;
            typedef const value_type&                       const_reference;
            typedef typename Allocator::pointer             pointer;
            typedef typename Allocator::const_pointer       const_pointer;
            typedef ft::Itmap< value_type >       			iterator;
            typedef ft::Itmap< value_type > 			    const_iterator;                     ///// remettre const
            typedef ft::reverse_iterator<iterator>          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
            // typedef typename Allocator::template rebind< std::allocator< Node<value_type> > >::other allocator_type;

            //------------------- Value compare : classe imbriquée -------------------//
            class value_compare : ft::binary_function<value_type, value_type, bool>
            {
				friend class map<key_type, mapped_type, key_compare, allocator_type>;

                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

                public:
                    /*Member typed*/
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;

                    /*Member function*/
                    bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
            };

            //------------------- Member functions : Constructor / Destructor + operator = -------------------//
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _comp(comp), _tree(BTree<key_type, mapped_type>()) {}                                                 /////// finir le constructor
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _comp(comp), _tree(BTree<key_type, mapped_type>())                 /////// finir le constructor
            {
                this->insert(first, last);
            }
            map (const map& x): _alloc(x._alloc), _comp(x._comp), _tree(x._tree) {}
            ~map() { /*_tree.clear(_tree.getRoot()); */}                                                                                                                                                                                               /////// faire le destructor

            map& operator=(const map& x)
            {
                iterator it = x.begin();
                size_type i = 0;

                if (this != &x)
                {
                    while (i < x.size())
                    {
                        this->insert(*it);
                        it++;
                        it++;
                    }
                    //this->clear();
                    //this->insert(x._tree.firstNode(), x._tree.lastNode());
                    this->_alloc = x._alloc;
                    this->_comp = x._comp;
                    this->_tree = x._tree;
                }
                return (*this);
            }

            //------------------- Member functions : Iterators -------------------//
            iterator begin() { return (iterator(_tree.firstNode(_tree.getRoot()))); }
            const_iterator begin() const { return (const_iterator(_tree.firstNode(_tree.getRoot()))); }
            iterator end() { return (iterator(_tree.lastNode(_tree.getRoot()))++); }
            const_iterator end() const { return (const_iterator(_tree.getEnd())); }
            reverse_iterator rbegin() { return (reverse_iterator(_tree.lastNode(_tree.getRoot()))); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(_tree.lastNode(_tree.getRoot()))); }
            reverse_iterator rend() { return (reverse_iterator(_tree.firstNode(_tree.getRoot()))); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(_tree.firstNode(_tree.getRoot()))); }

            //------------------- Member functions : Capacity -------------------//
            bool empty() const
            {
                if (_tree.getSize() == 0)
                    return (true);
                return (false);
            }
            size_type size() const { return (_tree.getSize()); }
            size_type max_size() const { return (allocator_type().max_size()); }

            //------------------- Member functions : Element access -------------------//
            mapped_type& operator[] (const key_type& k)
			{
                ft::Node<value_type>* ptr = _tree.search(k);

                if (ptr == u_nullptr)
                    ptr = _tree.insertNode(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
                //std::cout << &ptr->data.second << std::endl;
				return (ptr->data.second);
			}

            //------------------- Member functions : Modifiers -------------------//	

            pair<iterator,bool> insert(const value_type& val)
            {
                ft::Node<value_type>*   ptr;
                bool                    find = true;

                ptr = _tree.insertNode(val);
                if (ptr == u_nullptr)
                    find = false;
				return (ft::make_pair<iterator, bool>(iterator(ptr), find));
            }
            iterator insert (iterator position, const value_type& val)
            {
                (void)position;                                                                                                         ////// utilser it position
                return (iterator(_tree.insertNode(val)));
            }	
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
				iterator begin;
				iterator end;

				begin = first;
				end = last;
                if (begin->first > last->first)
                    return ;
                while (first <= last)
                {
                    _tree.insertNode(*begin);
                    first++;
                }
            }

            void erase(iterator position)
            {
                iterator it;

                while (it < position)
                {
                    it++;
                }
                if (it == position)
                {
                    _tree.deleteNode(it.base(), it->first);
                }
            }	
            size_type erase(const key_type& key)
            {
				return (_tree.deleteNode(_tree.getRoot(), key));
            }
            void erase(iterator first, iterator last)
            {
                if ((*first).first > (*last).first)
                    return ;
                while (first <= last)
                {
                    _tree.deleteNode(first.base(), (*first).first);
                    first++;
                }
            }

            void swap (map& x)                                                                           ////// remplacer BTree par un pointer sur tree dans map
            {
                _tree.swap(x._tree);
            }
            
            void clear()
			{
				_tree.clear(_tree.getRoot());
			}

            //------------------- Member functions : Observers -------------------//
            key_compare key_comp() const
            {
                return (_comp);
            }
            value_compare value_comp() const
            {
                return (value_compare(key_compare()));
            }

            //------------------- Member functions : Operations -------------------//
            iterator find (const key_type& k) { return (iterator(_tree.search(k))); }
            const_iterator find (const key_type& k) const { return (iterator(_tree.search(k))); }

            size_type count (const key_type& k) const
            {
                if (_tree.search(k) == u_nullptr)
                    return (0);
                return (1);
            }

            iterator lower_bound (const key_type& k)                  ////// Protection?
            {
                iterator it = this->begin();

                while ((*it).first <= k)
                    it++;
                return (it);
            }
            const_iterator lower_bound (const key_type& k) const
            {
                iterator it = this->begin();

                while ((*it).first <= k)
                    it++;
                return (it);
            }

            iterator upper_bound (const key_type& k)
            {
                iterator it = this->begin();

                while ((*it).first > k)
                    it++;
                return (it);
            }
            const_iterator upper_bound (const key_type& k) const
            {
                iterator it = this->begin();

                while ((*it).first > k)
                    it++;
                return (it);
            }

            pair<iterator,iterator> equal_range (const key_type& k)
            {
                return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
            }
            pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            {
                return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
            }

            //------------------- Member functions : Allocator -------------------//
            allocator_type get_allocator() const { return (allocator_type()); }

            void debug()                                                                                                                ///// enlever
            {
                _tree.printHelper(_tree.getRoot(), "", true);
            }

        private:
            allocator_type                              _alloc;
            key_compare                                 _comp;
			ft::BTree<key_type, mapped_type>			_tree;
    };

    //------------------- Non-member functions -------------------//
    template< class Key, class T, class Compare, class Alloc >
    bool operator==( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (!(lhs == rhs)); }
    template< class Key, class T, class Compare, class Alloc >
    bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
    template< class Key, class T, class Compare, class Alloc >
    bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (!(rhs < lhs)); }
    template< class Key, class T, class Compare, class Alloc >
    bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (rhs < lhs); }
    template< class Key, class T, class Compare, class Alloc >
    bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (!(lhs < rhs)); }
    template< class Key, class T, class Compare, class Alloc >
    void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) { lhs.swap(rhs); }
}

#endif 
