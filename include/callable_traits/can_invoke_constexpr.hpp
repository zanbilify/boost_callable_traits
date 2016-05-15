/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CAN_INVOKE_CONSTEXPR_HPP
#define CALLABLE_TRAITS_CAN_INVOKE_CONSTEXPR_HPP

#include <callable_traits/detail/can_invoke_constexpr_impl.hpp>
#include <callable_traits/detail/required_definitions.hpp>
#include <utility>

namespace callable_traits {

    template<typename T, typename... Args>
    inline constexpr auto
    can_invoke_constexpr(T&& t, Args&&... args) {
        return detail::can_invoke_constexpr_impl(
            ::std::forward<T>(t),
            ::std::forward<Args>(args)...
        );
    }

    template<typename... Args>
    inline constexpr auto
    can_invoke_constexpr() {
        return typename detail::can_invoke_constexpr_impl_types<
            detail::are_all_constexpr_constructible<Args...>::value,
            Args...
        >::type{};
    }
}

#endif
