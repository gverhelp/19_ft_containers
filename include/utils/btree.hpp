#ifndef BTREE_HPP
# define BTREE_HPP

# include "utils.hpp"
# include <iostream>
# include <memory>

namespace ft
{
    template < class T >
    struct Node
    {
        typedef T   value_type;

        value_type  data;
        Node*       parent;
        Node*       left;
        Node*       right;
        int         color;
    };

    template < class Key, class Value, class T = ft::pair< Key, Value >, class Node = ft::Node<T>, class Node_Alloc = std::allocator<Node> >
    class BTree
    {
        private:
            Node* root;

        public:
			typedef Key								key_type;
            typedef T                               value_type;
            typedef Node                            node_type;
            typedef Node*                           node_pointer;
            typedef Node_Alloc						node_alloc;
            typedef typename node_alloc::pointer    node_alloc_pointer;

			void rbTransplant(node_pointer u, node_pointer v)
			{
				if (u->parent == nullptr)
				{
					root = v;
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
					this->root = y;
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
					this->root = y;
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

			void fixDelete(node_pointer x)
			{
				node_pointer s;
				while (x != root && x->color == 0)
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
							x = root;
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
							x = root;
						}
					} 
				}
				x->color = 0;
			}

            node_pointer insert(const value_type& val)
            {
				/*Insert*/
                node_pointer tmp = this->root;
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
                    return (nullptr);
                node_pointer toInsert = node_alloc().allocate(1);
                toInsert->data.first = val.first;
                toInsert->data.second = val.second;
                toInsert->parent = parent;
                toInsert->left = nullptr;
                toInsert->right = nullptr;
                toInsert->color = 1;
                if (!this->root)
                {
					toInsert->color = 0;
                    this->root = toInsert;
                    return (toInsert);
                }
                else if (toInsert->data.first < parent->data.first)
                    parent->left = toInsert;
                else
                    parent->right = toInsert;
				
				/*Rebalance*/
				if (toInsert->parent->parent == nullptr)
					return (toInsert);
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
					if (toInsert == root)
					{
						break;
					}
				}
				this->root->color = 0;
                return (toInsert);
            }

			void delete_node(node_pointer node, int key)
			{
				// find the node containing key
				node_pointer z = nullptr;
				node_pointer x, y;
				while (node != nullptr)
				{
					if (node->data == key)
					{
						z = node;
					}

					if (node->data <= key)
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
					std::cout << "Couldn't find key in the tree" << std::endl;
					return;
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
				delete z;
				if (y_original_color == 0)
				{
					fixDelete(x);
				}
            }

            node_pointer search(const key_type& key)
            {
                node_pointer tmp = this->root;

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
    };
}

#endif