/*!
@file
Defines `flags`

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_GET_QUALIFIER_FLAGS_HPP
#define CALLABLE_TRAITS_GET_QUALIFIER_FLAGS_HPP

#include <callable_traits/detail/core.hpp>
#include <type_traits>
#include <cstdint>

namespace callable_traits {

    template<typename T>
    struct get_qualifier_flags
        : std::integral_constant<flags, detail::flag_map<T>::value> {
        using type = std::integral_constant<flags, detail::flag_map<T>::value>;
    };

    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T>
    struct get_qualifier_flags_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else

    template<typename T>
    constexpr flags get_qualifier_flags_v = detail::flag_map<T>::value;

    #endif
}

#endif //#ifndef CALLABLE_TRAITS_GET_QUALIFIER_FLAGS_HPP
