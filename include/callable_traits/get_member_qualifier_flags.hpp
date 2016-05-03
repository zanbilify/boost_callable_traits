/*!
@file
Defines `flags`

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_GET_MEMBER_QUALIFIER_FLAGS_HPP
#define CALLABLE_TRAITS_GET_MEMBER_QUALIFIER_FLAGS_HPP

#include <callable_traits/detail/required_definitions.hpp>
#include <type_traits>
#include <cstdint>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    get_member_qualifier_flags() {
        return std::integral_constant<flags, detail::traits<T>::q_flags>{};
    }

    template<typename T>
    inline constexpr flags
    get_member_qualifier_flags(T&&) {
        return get_member_qualifier_flags<T&&>();
    }
}

#endif //#ifndef CALLABLE_TRAITS_GET_MEMBER_QUALIFIER_FLAGS_HPP
