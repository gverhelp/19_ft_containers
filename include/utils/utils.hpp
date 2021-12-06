#ifndef UTILS_HPP
# define UTILS_HPP

# include <type_traits>

namespace ft
{
    /////////////////////////////////////////////
    //////////////////// MAP ////////////////////                   ////// Faire comp, rebind
    /////////////////////////////////////////////
	
    //------------------- Node -------------------//
	template < class T >
    struct Node
    {
        typedef T   value_type;

        value_type  data;
        Node*       parent;
        Node*       left;
        Node*       right;
        int         color;

        Node(): data(value_type()) {}
        Node(const value_type& val): data(val) {}
        Node(const Node& cpy): data(cpy.data), parent(cpy.parent), left(cpy.left), right(cpy.right), color(cpy.color) {}
        ~Node() {}

        Node& operator=(const Node& cpy)
        {
            if (this != &cpy)
            {
                this->data = cpy.data;
                this->parent = cpy.parent;
                this->left = cpy.left;
                this->right = cpy.right;
                this->color = cpy.color;
            }
            return (*this);
        }
    };

    //------------------- pair and make_pair -------------------//
    template < class T1, class T2 >
    struct pair
    {
        typedef T1  first_type;
        typedef T2  second_type;

        first_type  first;
        second_type second;

        pair(): first(first_type()), second(second_type()) {}
        template<class U, class V>
        pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {}
        pair (const first_type& a, const second_type& b) /*: first(a), second(b)*/ 
		{
			first = a;
			second = b;
		}
        /*pair& operator=(const pair& pr)
        {
            if (this != &pr)
            {
                first = pr.first;
                second = pr.second;
            }
            return (*this);
        }*/  					//////linux thing (chez moi ca marche pierre sale fdp)
    };

    // Non member pair //
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }
    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs==rhs); }
    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }
    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs<lhs); }
    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs<lhs; }
    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); }

    template < class T1, class T2 >
    pair<T1,T2> make_pair(T1 x, T2 y)
    {
        return (pair<T1,T2>(x, y));
    }

    //------------------- less -------------------//
    template < class Arg1, class Arg2, class Result >
    struct binary_function
    {
        typedef Arg1    first_argument_type;
        typedef Arg2    second_argument_type;
        typedef Result  result_type;
    };

    template < class T >
    struct less : binary_function <T, T, bool>
    {
        typedef T       first_argument_type;
        typedef T       second_argument_type;
        typedef bool    result_type;

        bool operator() (const T& x, const T& y) const { return x < y; }
    };

    /////////////////////////////////////////////
    //////////////////// ALL ////////////////////
    /////////////////////////////////////////////

    //------------------- nullptr -------------------//
    static class nullptr_t
    {
        public:
            template<class T>
            operator T*() const { return (0); }
            template<class C, class T>
            operator T C::*() const { return (0); }

        private:
            void operator&() const;

    }           u_nullptr = {};

    //------------------- Equal -------------------//
    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1!=last1)
        {
            if (!(*first1 == *first2))
                return false;
            ++first1; ++first2;
        }
        return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
    {
        while (first1!=last1)
        {
            if (!pred(*first1,*first2))
                return false;
            ++first1; ++first2;
        }
        return true;
    }

    //------------------- Lexicographical compare -------------------//
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
    	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
		{
        	if (*first1 < *first2) return true;
        	if (*first2 < *first1) return false;
    	}
    	return (first1 == last1) && (first2 != last2);
	}
	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
    	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) 
		{
        	if (comp(*first1, *first2)) return true;
        	if (comp(*first2, *first1)) return false;
    	}
    	return (first1 == last1) && (first2 != last2);
	}

    //------------------- Enable if -------------------//     //https://h-deb.clg.qc.ca/Sujets/TrucsScouts/Comprendre_enable_if.html
    template<bool B, class T = void>
    struct enable_if {};
 
    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;   // true or false vu qu'on passe un bool
        typedef T value_type;
        typedef integral_constant<T, v> type;
        operator T() { return v; }
    };

    template <class T>
    struct is_integral : public ft::integral_constant<bool, false> {};
    template<> struct is_integral<bool> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<char16_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<char32_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<wchar_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<signed char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<short int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<long long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned short int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<unsigned long long int> : public ft::integral_constant<bool, true> {};
    // const
    template<> struct is_integral<const bool> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const char16_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const char32_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const wchar_t> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const signed char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const short int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const long long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned char> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned short int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned long int> : public ft::integral_constant<bool, true> {};
    template<> struct is_integral<const unsigned long long int> : public ft::integral_constant<bool, true> {};
}

#endif
