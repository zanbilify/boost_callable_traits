/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_INVOKABLE_HPP
#define CALLABLE_TRAITS_IS_INVOKABLE_HPP

#include <callable_traits/detail/is_invokable_impl.hpp>
#include <callable_traits/detail/required_definitions.hpp>
#include <utility>

namespace callable_traits {

    template<typename... Args>
    inline constexpr auto
    is_invokable(Args&&... args) {
        return detail::is_invokable_impl(
            ::std::forward<Args>(args)...
        );
    }

    template<typename... Args>
    inline constexpr auto
    is_invokable() {
        return detail::is_invokable_impl<Args...>();
    }
}

#endif
