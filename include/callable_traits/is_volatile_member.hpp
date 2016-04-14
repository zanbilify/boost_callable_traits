/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_is_volatile_member_HPP
#define CALLABLE_TRAITS_is_volatile_member_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    is_volatile_member() {
        return typename detail::traits<T>::is_volatile_member{};
    }

    template<typename T>
    inline constexpr auto
    is_volatile_member(T&&) {
        return typename detail::traits<T&&>::is_volatile_member{};
    }
}

#endif
