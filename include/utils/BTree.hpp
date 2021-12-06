/*
- Insert et delete avec rebalance de rbtree
- remplacer end par u_u_nullptr
- reimplementer u_nullptr
- recuperer search et clear et size
- implementer la size dans insert et delete
- faire swap dans rbtree
*/

#ifndef BTREE_HPP
# define BTREE_HPP

# include "utils.hpp"

namespace ft
{
    template < class Key, class T >
    class BTree
    {
        public:

            typedef size_t                                  size_type;
            typedef T                                       mapped_type;
            typedef Key                                     key_type;
            typedef ft::pair<const key_type, mapped_type>   value_type;
            typedef std::allocator< Node<value_type> >      node_allocator;
			typedef ft::Node<value_type>*					node_pointer;
            typedef ft::Node<value_type>                    node_type;

            //------------------- Constructor and destructor -------------------//
            BTree()
            {
                end = node_allocator().allocate(1);
                node_allocator().construct(end, node_type());
                end->parent = u_nullptr;
                end->left = u_nullptr;
                end->right = u_nullptr;
                end->color = 0;
                root = end;
				size = 0;
            }
            BTree(const BTree& cpy): root(cpy.root), end(cpy.end), size(cpy.size)
            {
                this->clear(this->root);
                this->insertAll(cpy.root);
            }
            ~BTree() 
			{
				node_allocator().destroy(end);
				node_allocator().deallocate(end, 1);
				end = nullptr;
			}

            BTree& operator=(const BTree& cpy)
            {
                if (this != &cpy)
                {
                    this->clear(this->root);
                    this->insertAll(cpy.root);
                    this->root = cpy.root;
                    this->end = cpy.end;
                    this->size = cpy.size;
                }
                return (*this);
            }

            //------------------- Member functions -------------------//
            node_pointer insertNode(const value_type& val) 
            {
				node_pointer find;

                if ((find = search(val.first)) != u_nullptr)
                    return (find);
                node_pointer node = node_allocator().allocate(1);
				node_allocator().construct(node, node_type(ft::make_pair<key_type, mapped_type>(val.first, val.second)));
                node->parent = u_nullptr;
                node->left = end;
                node->right = end;
                node->color = 1;
                size++;

                node_pointer y = u_nullptr;
                node_pointer x = this->root;

                while (x != end)
                {
                    y = x;
                    if (node->data < x->data)
                    {
                        x = x->left;
                    }
                    else
                    {
                        x = x->right;
                    }
                }
                node->parent = y;
                if (y == u_nullptr)
                {
                    root = node;
                }
                else if (node->data < y->data)
                {
                    y->left = node;
                }
                else
                {
                    y->right = node;
                }
                if (node->parent == u_nullptr)
                {
                    node->color = 0;
					indexEnd();
                    return (node);
                }
                if (node->parent->parent == u_nullptr)
                {
					indexEnd();
                    return (node);
                }
                rebalInsert(node);
				indexEnd();
                return (node);
            }

			void insertAll(node_pointer node)
			{
				if (node == u_nullptr)
					return ;
				insertAll(node->left);
				insertAll(node->right);
				insertNode(node->data);
            }

            size_type deleteNode(node_pointer node, const key_type& key)
            {
                node_pointer z = end;
                node_pointer x, y;

                while (node != end)
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
                if (z == end)
                    return 0;
                y = z;
                int y_original_color = y->color;
                if (z->left == end)
                {
                    x = z->right;
                    rbTransplant(z, z->right);
                }
                else if (z->right == end)
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
                        x->parent = y;
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
                node_allocator().destroy(z);
                node_allocator().deallocate(z, 1);
                size--;
                if (y_original_color == 0)
                {
                    rebalDelete(x);
                }
				indexEnd();
                return (1);
            }

			void clear(node_pointer node)
			{
				if (node == end)
					return ;
			
				/* first delete both subtrees */
				clear(node->left);
				clear(node->right);
				
				/* then delete the node */
				//std::cout << "\n Deleting node: " << node->data.first;
				node_allocator().destroy(node);
				node_allocator().deallocate(node, 1);
				node = nullptr;
            }

            node_pointer search(const key_type& key) const
            {
                node_pointer tmp = this->root;

                while (tmp != end)
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
                return (u_nullptr);
            }

            void swap(BTree& x)
            {
                size_type       swap_size;
                node_pointer    swap_root;
                node_pointer    swap_end;

                swap_size = x.size;
                swap_root = x.root;
                swap_end = x.end;
                x.size = this->size;
                x.root = this->root;
                x.end = this->end;
                this->size = swap_size;
                this->root = swap_root;
                this->end = swap_end;
            }
            node_pointer firstNode() const
            {
				node_pointer tmp = root;
	
				if (tmp == end)
					return (end);
                while (tmp->left != end)
                {
                    tmp = tmp->left;
                }
                return tmp;
            }
            node_pointer lastNode()
            {
				node_pointer tmp = root;

				if (tmp == end)
					return (end);
                while (tmp->right != end)
                {
                    tmp = tmp->right;
                }
                return (tmp);
            }
			
			node_pointer getEnd() const { return (this->end); }
            node_pointer getRoot() const { return (this->root); }
            size_type getSize() const { return (this->size); }

            void printHelper(node_pointer root, std::string indent, bool last)
            {
                // print the tree structure on the screen
                if (root != end)
                {
                    std::cout<<indent;
                    if (last)
                    {
                        std::cout<<"R----";
                        indent += "     ";
                    }
                    else
                    {
                        std::cout<<"L----";
                        indent += "|    ";
                    }
                    std::string sColor = root->color?"RED":"BLACK";
                    std::cout<<root->data.first<<"("<<sColor<<")"<<std::endl;
                    printHelper(root->left, indent, false);
                    printHelper(root->right, indent, true);
                }
                // std::cout<<root->left->data<<std::endl;
            }

        private:
            node_pointer    root;
            node_pointer    end;
            size_type       size;
			
			void indexEnd()										////a virer
			{
				end->left = firstNode();
				end->right = lastNode();
			}	
			node_pointer minimum(node_pointer node) 
			{
				while (node->left != end) 
				{
					node = node->left;
				}
				return node;
			}
            void rbTransplant(node_pointer u, node_pointer v)
            {
                if (u->parent == u_nullptr)
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
            void leftRotate(node_pointer x)
            {
                node_pointer y = x->right;
                x->right = y->left;
                if (y->left != end)
                {
                    y->left->parent = x;
                }
                y->parent = x->parent;
                if (x->parent == u_nullptr)
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

            void rightRotate(node_pointer x)
            {
                node_pointer y = x->left;
                x->left = y->right;
                if (y->right != end)
                {
                    y->right->parent = x;
                }
                y->parent = x->parent;
                if (x->parent == u_nullptr)
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

            void rebalInsert(node_pointer k)
            {
                node_pointer u;
                while (k->parent->color == 1)
                {
                    if (k->parent == k->parent->parent->right)
                    {
                        u = k->parent->parent->left; // uncle
                        if (u->color == 1)
                        {
                            // case 3.1
                            u->color = 0;
                            k->parent->color = 0;
                            k->parent->parent->color = 1;
                            k = k->parent->parent;
                        }
                        else
                        {
                            if (k == k->parent->left)
                            {
                                // case 3.2.2
                                k = k->parent;
                                rightRotate(k);
                            }
                            // case 3.2.1
                            k->parent->color = 0;
                            k->parent->parent->color = 1;
                            leftRotate(k->parent->parent);
                        }
                    }
                    else
                    {
                        u = k->parent->parent->right; // uncle
                        if (u->color == 1) {
                            // mirror case 3.1
                            u->color = 0;
                            k->parent->color = 0;
                            k->parent->parent->color = 1;
                            k = k->parent->parent;	
                        }
                        else
                        {
                            if (k == k->parent->right)
                            {
                                // mirror case 3.2.2
                                k = k->parent;
                                leftRotate(k);
                            }
                            // mirror case 3.2.1
                            k->parent->color = 0;
                            k->parent->parent->color = 1;
                            rightRotate(k->parent->parent);
                        }
                    }
                    if (k == root)
                    {
                        break;
                    }
                }
                root->color = 0;
            }
            void rebalDelete(node_pointer x)
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
                        if (s->left->color == 0 && s->right->color == 0)
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
    };
}

#endif
