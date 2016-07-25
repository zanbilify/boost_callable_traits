/*
Copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_POLYFILLS_CONJUNCTION_HPP
#define CALLABLE_TRAITS_DETAIL_POLYFILLS_CONJUNCTION_HPP

#undef CALLABLE_TRAITS_CONJUNCTION
#define CALLABLE_TRAITS_CONJUNCTION(...) \
::callable_traits::detail::polyfills::conjunction<__VA_ARGS__>


CALLABLE_TRAITS_DETAIL_NAMESPACE_BEGIN

namespace polyfills {
    
//polyfill for C++17 std::conjunction
template<typename...>
struct conjunction
    : std::true_type {};

template<typename T>
struct conjunction<T>
    : T {};

template<typename T, typename... Ts>
struct conjunction<T, Ts...>
    : std::conditional<T::value != false, T, conjunction<Ts...>>::type {};
    
}

CALLABLE_TRAITS_DETAIL_NAMESPACE_END

#endif
