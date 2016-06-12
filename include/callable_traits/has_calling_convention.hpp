/*!
@file add_member_const

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_CALLING_CONVENTION_HPP
#define CALLABLE_TRAITS_HAS_CALLING_CONVENTION_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/calling_conventions.hpp>
#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T, typename Tag>
    struct has_calling_convention
        : detail::has_calling_convention_t<T, Tag>::type {
        using type = typename detail::has_calling_convention_t<T, Tag>::type;
    };

    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T, typename>
    struct has_calling_convention_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else

    template<typename T, typename Tag>
    constexpr bool has_calling_convention_v =
        detail::has_calling_convention_t<T, Tag>::type::value;

    #endif
}

#endif //CALLABLE_TRAITS_HAS_CALLING_CONVENTION_HPP
