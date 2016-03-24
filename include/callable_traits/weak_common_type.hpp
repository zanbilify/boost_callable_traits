/*!
Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
Copyright (c) 2001 David Abrahams
Copyright (c) 2005 Peter Dimov
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_WEAK_COMMON_TYPE_HPP
#define CALLABLE_TRAITS_WEAK_COMMON_TYPE_HPP

#include <type_traits>

namespace callable_traits {
    
    namespace ctdetail {

        template <typename BoolType, typename... Ts>
        struct weak_common_type_t;
 
        template <class T>
        struct weak_common_type_t<std::true_type, T> {
            using type = T;
        };
         
        template <class T, class U>
        struct weak_common_type_t<
            std::integral_constant<
                bool,
                !std::is_convertible<U, T>::value && std::is_convertible<T, U>::value
            >, T, U
        > {
            using type = T;
        };

        template <class T, class U>
        struct weak_common_type_t<
            std::integral_constant<
                bool,
                std::is_convertible<U, T>::value && !std::is_convertible<T, U>::value
            >, T, U
        > {
            using type = U;
        };

        template <class T, class U>
        struct weak_common_type_t<
            std::integral_constant<
                bool,
                !std::is_convertible<U, T>::value && !std::is_convertible<T, U>::value
            >, T, U
        > {
            using type = T;
        };
         
        template <class T, class U>
        struct weak_common_type_t<
            std::integral_constant<
            bool,
            std::is_same<U, T>::value
            >, T, U
        > {
            using type = T;
        };

        template <typename BoolType, class T, class U, class... V>
        struct weak_common_type_t<BoolType, T, U, V...> {

            using type = typename weak_common_type_t<
                std::true_type,
                typename weak_common_type_t<std::true_type, T, U>::type,
                V...
            >::type;
        };

        template<typename... Ts>
        using weak_common_type = typename weak_common_type_t<std::true_type, Ts...>::type;
    }
}

#endif