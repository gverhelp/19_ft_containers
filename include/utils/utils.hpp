#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
    /////////////////////////////////////////////
    //////////////////// MAP ////////////////////                   ////// Faire comp, rebind
    /////////////////////////////////////////////
    template < class T1, class T2 >
    struct pair
    {
        typedef T1  first_type;
        typedef T2  second_type;

        first_type  first;
        second_type second;

        pair() {}
        template<class U, class V>
        pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {}
        pair (const first_type& a, const second_type& b): first(a), second(b) {}
    };

    template < class T1, class T2 >
    pair<T1,T2> make_pair(T1 x, T2 y)
    {
        return (pair<T1,T2>(x, y));
    }

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

    // //------------------- nullptr -------------------//       //https://stackoverflow.com/questions/44517556/how-to-define-our-own-nullptr-in-c98
    // const                         /* this is a const object...     */
    // class nullptr_t
    // {
    //     public:
    //         template<class T>               /* convertible to any type       */
    //         operator T*() const             /* of null non-member            */
    //         { return 0; }                   /* pointer...                    */

    //         template<class C, class T>      /* or any type of null           */
    //         operator T C::*() const         /* member pointer...             */
    //         { return 0; }   

    //     private:
    //         void operator&() const;         /* Can't take address of nullptr */

    // }   nullptr = {};

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