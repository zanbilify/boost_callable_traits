/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CAN_INVOKE_HPP
#define CALLABLE_TRAITS_CAN_INVOKE_HPP

#include <callable_traits/detail/can_invoke_impl.hpp>
#include <callable_traits/detail/required_definitions.hpp>
#include <utility>

namespace callable_traits {

    template<typename... Args>
    inline constexpr auto
    can_invoke(Args&&... args) {
        return detail::can_invoke_impl(
            ::std::forward<Args>(args)...
        );
    }
}

#endif
