/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_LVALUE_REFERENCE_MEMBER_HPP
#define CALLABLE_TRAITS_IS_LVALUE_REFERENCE_MEMBER_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T>
    struct is_lvalue_reference_member
        : detail::traits<T>::is_lvalue_reference_member {

        using type = typename detail::traits<T>::is_lvalue_reference_member;
    };

    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T>
    struct is_lvalue_reference_member_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else

    template<typename T>
    constexpr bool is_lvalue_reference_member_v =
        detail::traits<T>::is_lvalue_reference_member::value;

    #endif
}

#endif
