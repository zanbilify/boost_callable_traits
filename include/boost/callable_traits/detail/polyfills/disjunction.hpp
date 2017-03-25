/*
Copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_POLYFILLS_DISJUNCTION_HPP
#define BOOST_CLBL_TRTS_DETAIL_POLYFILLS_DISJUNCTION_HPP

#undef BOOST_CLBL_TRTS_DISJUNCTION
#define BOOST_CLBL_TRTS_DISJUNCTION(...) \
::boost::callable_traits::detail::polyfills::disjunction<__VA_ARGS__>


BOOST_CLBL_TRTS_DETAIL_NAMESPACE_BEGIN

namespace polyfills {
    
    //polyfill for C++17 std::disjunction
    template<typename...>
    struct disjunction
        : std::false_type {};

    template<typename T>
    struct disjunction<T>
        : T {};

    template<typename T, typename... Ts>
    struct disjunction<T, Ts...>
        : std::conditional<T::value != false, T, disjunction<Ts...>>::type {};
    
}

BOOST_CLBL_TRTS_DETAIL_NAMESPACE_END

#endif
