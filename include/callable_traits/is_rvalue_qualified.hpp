/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_RVALUE_QUALIFIED_HPP
#define CALLABLE_TRAITS_IS_RVALUE_QUALIFIED_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    is_rvalue_qualified() {
        return typename detail::traits<T>::is_rvalue_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_rvalue_qualified(T&&) {
        return typename detail::traits<T&&>::is_rvalue_reference_qualified{};
    }
}

#endif
