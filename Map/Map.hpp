#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include <utility>

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
    class map
    {

    };
}

#endif