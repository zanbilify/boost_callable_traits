/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_VOID_RETURN_HPP
#define CALLABLE_TRAITS_HAS_VOID_RETURN_HPP

#include <callable_traits/result_of.hpp>
#include <callable_traits/detail/core.hpp>
#include <type_traits>

namespace callable_traits {

    template<typename T>
    struct has_void_return
        : std::is_same<typename detail::traits<T>::return_type, void> {};

    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T>
    struct has_void_return_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else

    template<typename T>
    constexpr bool has_void_return_v =
        std::is_same<typename detail::traits<T>::return_type, void>::value;

    #endif
}

#endif
