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
    inline constexpr auto
    get_qualifier_flags() {
        return std::integral_constant<flags, detail::flag_map<T>::value>{};
    }

    template<typename T>
    inline constexpr auto
    get_qualifier_flags(T&&) {
        using no_ref = typename std::remove_reference<T>::type;
        return get_qualifier_flags<no_ref>();
    }
}

#endif //#ifndef CALLABLE_TRAITS_GET_QUALIFIER_FLAGS_HPP
