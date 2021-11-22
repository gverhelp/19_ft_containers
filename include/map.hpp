#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include <utility>
# include "utils/utils.hpp"
# include "utils/btree.hpp"

namespace ft
{
    template < class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        public:
            typedef Key                                     key_type;
            typedef T                                       mapped_type;
            typedef ft::pair<const key_type, mapped_type>   value_type;
            typedef size_t                                  size_type;
            typedef ptrdiff_t                               difference_type;
            typedef Compare                                 key_compare;
            typedef Allocator                               allocator_type;
            typedef value_type&                             reference;
            typedef const value_type&                       const_reference;
            typedef typename Allocator::pointer             pointer;
            typedef typename Allocator::const_pointer       const_pointer;
            //typedef "LegacyBidirectionalIterator to value_type" iterator;
            //typedef "LegacyBidirectionalIterator to const value_type" const_iterator;
            //typedef std::reverse_iterator<iterator> reverse_iterator;
            //typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

            //------------------- Value compare : classe imbriquée -------------------//
            class value_compare : 
            {
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
            }

            //------------------- Member functions : Constructor / Destructor + operator = -------------------//
/*            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _size(0), _tree(BTree())
            {

            }
*/
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(BTree()), _size(0)
            {
                while (first <= last)
                    _tree.insert(*first);
            }
            //map (const map& x) {}
            //~map() {}

            //map& operator=(const map& x) {}

            //------------------- Member functions : Iterators -------------------//
            iterator begin() { return (iterator(_tree->firstnode())); }
            const_iterator begin() const { return (iterator(_tree->firstnode())); }
            iterator end() { return (iterator(_tree->lastnode())++); }
            const_iterator end() const { return (iterator(_tree->lastnode())++); }
            reverse_iterator rbegin() { return (iterator(_tree->lastnode())); }
            const_reverse_iterator rbegin() const { return (iterator(_tree->lastnode())); }
            reverse_iterator rend() { return (iterator(_tree->firstnode())); }
            const_reverse_iterator rend() const { return (iterator(_tree->firstnode())); }

            //------------------- Member functions : Capacity -------------------//
            bool empty() const
            {
                if (this->_size == 0)
                    return (true);
                return (false);
            }
            size_type size() const { return (_tree.getSize()); }
            size_type max_size() const { return (_tree.getMaxSize()); }

            //------------------- Member functions : Element access -------------------//
            mapped_type& operator[] (const key_type& k) { return (*(iterator(_tree.search(k)))); }

            //------------------- Member functions : Modifiers -------------------//	

            //pair<iterator,bool> insert(const value_type& val) {}
            iterator insert (iterator position, const value_type& val)
            {
                return (iterator(_tree.insert(val)));    ///// à vérifier
            }	
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                if ((*first).first > (*last).first)
                    return ;
                while (first <= last)
                {
                    _tree.insert((*first).first);
                    first++;
                }
            }

            void erase(iterator position)
            {
                _tree.delete_node((*position).first); /// fleche renvoie pair?
            }	
            size_type erase(const key_type& k)
            {
                _tree.delete_node(k);
                return (1);                            ///// verifier le return
            }
            void erase(iterator first, iterator last)
            {
                if ((*first).first > (*last).first)
                    return ;
                while (first <= last)
                {
                    _tree.delete_node((*first).first);
                    first++;
                }
            }
/*
            void swap (map& x)               ////// remplacer BTree par un pointer sur root dans map
            {
                size_t          swap_size;
                ft::Node<T>*    swap_root;

                swap_size = x._size;
                swap_root = x._root;
                x._size = this->_size;
                x._root = this->_root;
            }
*/            
            void clear() { _tree.clear_all(); }

            //------------------- Member functions : Observers -------------------//
            key_compare key_comp() const
            {
                return (_comp);
            }
            value_compare value_comp() const
            {
                return (value_compare());
            }

            //------------------- Member functions : Operations -------------------//
            iterator find (const key_type& k) { return (iterator(_tree.search(k))); }
            const_iterator find (const key_type& k) const { return (iterator(_tree.search(k))); }

            size_type count (const key_type& k) const
            {
                if (_tree.search(k) == nullptr)
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

            //pair<iterator,iterator> equal_range (const key_type& k) {}                            ///// Nique sa mère : impinnable
            //pair<const_iterator,const_iterator> equal_range (const key_type& k) const {}

            //------------------- Member functions : Allocator -------------------//
            allocator_type get_allocator() const { return (this->_alloc); }

        private:
            allocator_type                              _alloc;
            key_compare                                 _comp;
            BTree<key_type, mapped_type, value_type>    _tree;
            size_type                                   _size;     ///// mettre à jour size partout
            ft::Node<T>*                                _root;     ///// mettre à jour root partout

    };

    //------------------- Non-member functions -------------------//
    template< class Key, class T, class Compare, class Alloc >
    bool operator==( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs )
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t a = 0; a < lhs.size(); a++)
        {
            if (lhs[a] != rhs[a])
                return false;
        }
        return true;
    }
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