#ifndef BTREE_HPP
# define BTREE_HPP

# include "utils.hpp"
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

    template < class T, class Compare = ft::less<T>, class Node = ft::Node<T>, class Node_Alloc = std::allocator<Node> >
    class BTree
    {
        public:
            typedef T                               value_type;
            typedef Node                            node_type;
            typedef Node*                           node_pointer;
            typedef Compare                         key_compare;
            typedef Node_Alloc                      node_alloc;
            typedef typename node_alloc::pointer    pointer;

            pointer insert(const value_type& val)
            {
                pointer tmp = this->root;
                pointer parent = nullptr;

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
                pointer toInsert = node_alloc.allocate(1);
                toInsert->data.first = val.first;
                toInsert->data.second = val.second;
                toInsert->parent = parent;
                toInsert.left = nullptr;
                toInsert.right = nullptr;
                toInsert.color = 0;
                if (!this->root)
                {
                    this->root = toInsert;
                    return (toInsert);
                }
                else if (toInsert->data.first < parent->data.first)
                    parent->left = toInsert;
                else
                    parent->right = toInsert;
                return (toInsert);
            }

            delete(const value_type& val)
            {
                pointer tmp = this->root;
                pointer a = tmp;
                pointer b, c;
                while (tmp)
                {
                    if (tmp->data.first = val.first)
                        a = tmp;
                    if (tmp->data.first <= val.first)
                        tmp = tmp->right;
                    else
                        tmp = tmp->left;
                }
                if (a = tmp) //// pas trouve de key correspondante
                    return (nullptr);
            }

            search(const value_type& val)
            {
                pointer tmp = this->root;

                while (tmp)
                {
                    if (tmp->data.first == val.first)
                        return (tmp);
                    else if (val.first < tmp->data.first)
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

//            fix()
//            {

//            }

        private:
            node_pointer root;
    };
}

#endif