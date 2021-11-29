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
# include "utils/utils.hpp"
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
            typedef ft::Itmap< const value_type > 			const_iterator;
            typedef ft::reverse_iterator<iterator>          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
			typedef ft::Node<value_type>*					node_pointer;
            typedef ft::Node<value_type>                    node_type;
			typedef std::allocator< Node<value_type> >      node_allocator;
            //typedef typename Allocator::template rebind< std::allocator< Node<value_type> > >::other allocator_type;

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
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _comp(comp), _size(0), _root(nullptr) {}                                                 /////// finir le constructor
            template <class InputIterator>
            map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _comp(comp), _size(0), _root(nullptr)                 /////// finir le constructor
            {
                this->insert(first, last);
            }
            map (const map& x): _alloc(x._alloc), _comp(x._comp), _size(0), _root(nullptr) {
				//this->insert(x.begin(), x.end());
			}
            ~map() { this->clear(); }                                                                                                                                                                                               /////// faire le destructor

            //map& operator=(const map& x) {}

            //------------------- Member functions : Iterators -------------------//
            iterator begin() { return (iterator(this->firstNode())); }
            const_iterator begin() const { return (const_iterator(this->firstNode())); }
            iterator end() { return (iterator(this->lastNode())++); }
            const_iterator end() const { return (const_iterator(this->lastNode())++); }
            reverse_iterator rbegin() { return (reverse_iterator(this->lastNode())); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->lastNode())); }
            reverse_iterator rend() { return (reverse_iterator(this->firstNode())); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(this->firstNode())); }

            //------------------- Member functions : Capacity -------------------//
            bool empty() const
            {
                if (this->_size == 0)
                    return (true);
                return (false);
            }
            size_type size() const { return (this->_size); }
            size_type max_size() const { return (allocator_type().max_size()); }

            //------------------- Member functions : Element access -------------------//
            mapped_type& operator[] (const key_type& k)
			{
				iterator it(this->search(k));
 
				return (it->second);
			}

            //------------------- Member functions : Modifiers -------------------//	

            pair<iterator,bool> insert(const value_type& val)
            {
				return (this->insertNode(val));
            }
            iterator insert (iterator position, const value_type& val)
            {
                (void)position;                                                                                                         ////// utilser it position
                return (iterator(this->insertNode(val).first));
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
                    this->insertNode(*begin);
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
                    this->deleteNode((*it).first);
                }
            }	
            size_type erase(const key_type& key)
            {
				return (this->deleteNode(key));
            }
            void erase(iterator first, iterator last)
            {
                if ((*first).first > (*last).first)
                    return ;
                while (first <= last)
                {
                    this->deleteNode((*first).first);
                    first++;
                }
            }

            void swap (map& x)                                                                           ////// remplacer BTree par un pointer sur root dans map
            {
                size_t          swap_size;
                node_pointer    swap_root;

                swap_size = x._size;
                swap_root = x._root;
                x._size = this->_size;
                x._root = this->_root;
            }
            
            void clear()
			{
				this->recurClear(this->_root);
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
            iterator find (const key_type& k) { return (iterator(this->search(k))); }
            const_iterator find (const key_type& k) const { return (iterator(this->search(k))); }

            size_type count (const key_type& k) const
            {
                if (this->search(k) == nullptr)
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

        private:
            allocator_type                              _alloc;
            key_compare                                 _comp;
            size_type                                   _size;     ///// mettre à jour size partout
            node_pointer                                _root;     ///// mettre à jour root partout

			node_pointer minimum(node_pointer node)
			{
				while (node->left != nullptr)
				{
					node = node->left;
				}
				return (node);
			}
			void rbTransplant(node_pointer u, node_pointer v)
			{
				if (u->parent == nullptr)
				{
					_root = v;
				}
				else if (u == u->parent->left)
				{
					u->parent->left = v;
				}
				else
				{
					u->parent->right = v;
				}
				v->parent = u->parent;
			}

			void rightRotate(node_pointer x)
			{
				node_pointer y = x->left;
				x->left = y->right;
				if (y->right != nullptr)
				{
					y->right->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == nullptr)
				{
					this->_root = y;
				}
				else if (x == x->parent->right)
				{
					x->parent->right = y;
				}
				else
				{
					x->parent->left = y;
				}
				y->right = x;
				x->parent = y;
			}

			void leftRotate(node_pointer x)
			{
				node_pointer y = x->right;
				x->right = y->left;
				if (y->left != nullptr)
				{
					y->left->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == nullptr)
				{
					this->_root = y;
				}
				else if (x == x->parent->left)
				{
					x->parent->left = y;
				}
				else
				{
					x->parent->right = y;
				}
				y->left = x;
				x->parent = y;
			}

			void rebalDelete(node_pointer x)
			{
				node_pointer s;
				while (x != _root && x->color == 0)
				{
					if (x == x->parent->left)
					{
						s = x->parent->right;
						if (s->color == 1)
						{
							// case 3.1
							s->color = 0;
							x->parent->color = 1;
							leftRotate(x->parent);
							s = x->parent->right;
						}

						if (s->left->color == 0 && s->right->color == 0)
						{
							// case 3.2
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->right->color == 0)
							{
								// case 3.3
								s->left->color = 0;
								s->color = 1;
								rightRotate(s);
								s = x->parent->right;
							}

							// case 3.4
							s->color = x->parent->color;
							x->parent->color = 0;
							s->right->color = 0;
							leftRotate(x->parent);
							x = _root;
						}
					}
					else
					{
						s = x->parent->left;
						if (s->color == 1)
						{
							// case 3.1
							s->color = 0;
							x->parent->color = 1;
							rightRotate(x->parent);
							s = x->parent->left;
						}

						if (s->right->color == 0 && s->right->color == 0)
						{
							// case 3.2
							s->color = 1;
							x = x->parent;
						}
						else
						{
							if (s->left->color == 0)
							{
								// case 3.3
								s->right->color = 0;
								s->color = 1;
								leftRotate(s);
								s = x->parent->left;
							}

							// case 3.4
							s->color = x->parent->color;
							x->parent->color = 0;
							s->left->color = 0;
							rightRotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = 0;
			}
            size_type deleteNode(const key_type& key)
            {
				// find the node containing key
				node_pointer z = nullptr;
				node_pointer x, y;
				node_pointer node = this->_root;
				while (node != nullptr)
				{
					if (node->data.first == key)
					{
						z = node;
					}
					if (node->data.first <= key)
					{
						node = node->right;
					}
					else
					{
						node = node->left;
					}
				}
				if (z == nullptr)
				{
					//std::cout << "Couldn't find key in the tree" << std::endl;
					return 0;
				}
				y = z;
				int y_original_color = y->color;
				if (z->left == nullptr)
				{
					x = z->right;
					rbTransplant(z, z->right);
				}
				else if (z->right == nullptr)
				{
					x = z->left;
					rbTransplant(z, z->left);
				}
				else
				{
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
					{
						x->parent = y;
					}
					else
					{
						rbTransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					rbTransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				_size--;
				node_allocator().destroy(z);
				node_allocator().deallocate(z, 1);
				z = nullptr;
				if (y_original_color == 0)
				{
					rebalDelete(x);
				}
				return (1);
            }
			void rebalInsert(node_pointer toInsert)
            {
				/*Rebalance*/
                node_pointer tmp;

				if (toInsert->parent->parent == nullptr)
					return ;
                while (toInsert->parent->color == 1)
				{
					if (toInsert->parent == toInsert->parent->parent->right)
					{
						tmp = toInsert->parent->parent->left; // uncle
						if (tmp->color == 1)
						{
							// case 3.1
							tmp->color = 0;
							toInsert->parent->color = 0;
							toInsert->parent->parent->color = 1;
							toInsert = toInsert->parent->parent;
						}
						else
						{
							if (toInsert == toInsert->parent->left)
							{
								// case 3.2.2
								toInsert = toInsert->parent;
								rightRotate(toInsert);
							}
							// case 3.2.1
							toInsert->parent->color = 0;
							toInsert->parent->parent->color = 1;
							leftRotate(toInsert->parent->parent);
						}
					}
					else
					{
						tmp = toInsert->parent->parent->right; // uncle
						if (tmp->color == 1)
						{
							// mirror case 3.1
							tmp->color = 0;
							toInsert->parent->color = 0;
							toInsert->parent->parent->color = 1;
							toInsert = toInsert->parent->parent;	
						}
						else
						{
							if (toInsert == toInsert->parent->right)
							{
								// mirror case 3.2.2
								toInsert = toInsert->parent;
								leftRotate(toInsert);
							}
							// mirror case 3.2.1
							toInsert->parent->color = 0;
							toInsert->parent->parent->color = 1;
							rightRotate(toInsert->parent->parent);
						}
					}
					if (toInsert == _root)
					{
						break;
					}
				}
				this->_root->color = 0;
            }
			pair<iterator,bool> insertNode(const value_type& val)
			{
                node_pointer tmp = this->_root;
                node_pointer parent = nullptr;

                while (tmp)
                {
                    parent = tmp;
                    if (val.first < tmp->data.first)
                        tmp = tmp->left;
                    else
                        tmp = tmp->right;
                }
                if (parent && (val.first == parent->data.first))
                    return (ft::make_pair<iterator, bool>(iterator(parent), false));
                node_pointer toInsert = node_allocator().allocate(1);
				node_allocator().construct(toInsert, node_type(ft::pair<key_type, mapped_type>(val.first, val.second)));
                // /toInsert->data = ft::pair<key_type, mapped_type>(val.first, val.second);												/////// MAKE_PAIR
                toInsert->parent = parent;
                toInsert->left = nullptr;
                toInsert->right = nullptr;
                toInsert->color = 1;
				_size++;
                if (!this->_root)
                {
					toInsert->color = 0;
                    this->_root = toInsert;
                    return (ft::make_pair<iterator, bool>(iterator(this->_root), true));
                }
                else if (toInsert->data.first < parent->data.first)
                    parent->left = toInsert;
                else
                    parent->right = toInsert;
                rebalInsert(toInsert);
                return (ft::make_pair<iterator, bool>(iterator(toInsert), true));
			}
            node_pointer search(const key_type& key) const
            {
                node_pointer tmp = this->_root;

                while (tmp)
                {
                    if (tmp->data.first == key)
                        return (tmp);
                    else if (key < tmp->data.first)
                    {
                        tmp = tmp->left;
                    }
                    else
                    {
                        tmp = tmp->right;
                    }   
                }
                return (nullptr);
            }
			node_pointer lastNode()
			{
				node_pointer last = this->_root;

				while (last && last->right != nullptr)
					last = last->right;
				return (last);
			}

			node_pointer firstNode() const
			{
				node_pointer first = this->_root;

				while (first && first->left != nullptr)
					first = first->left;
				return (first);
			}
			void recurClear(node_pointer node)
			{
				if (node == nullptr)
					return ;
			
				/* first delete both subtrees */
				recurClear(node->left);
				recurClear(node->right);
				
				/* then delete the node */
				//std::cout << "\n Deleting node: " << node->data;
				node_allocator().destroy(node);
				node_allocator().deallocate(node, 1);
				node = nullptr;
			}
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
