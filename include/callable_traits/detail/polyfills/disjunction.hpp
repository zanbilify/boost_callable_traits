/*
Copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_POLYFILLS_DISJUNCTION_HPP
#define CALLABLE_TRAITS_DETAIL_POLYFILLS_DISJUNCTION_HPP

#undef CALLABLE_TRAITS_DISJUNCTION
#define CALLABLE_TRAITS_DISJUNCTION(...) \
::callable_traits::detail::polyfills::disjunction<__VA_ARGS__>


CALLABLE_TRAITS_DETAIL_NAMESPACE_BEGIN

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

CALLABLE_TRAITS_DETAIL_NAMESPACE_END

#endif
