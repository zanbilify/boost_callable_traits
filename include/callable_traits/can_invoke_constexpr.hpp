/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CAN_INVOKE_CONSTEXPR_HPP
#define CALLABLE_TRAITS_CAN_INVOKE_CONSTEXPR_HPP

#include <callable_traits/detail/can_invoke_constexpr_impl.hpp>
#include <utility>

namespace callable_traits {

    template<typename... Args>
    inline constexpr auto
    can_invoke_constexpr(Args&&... args) {
        return detail::can_invoke_constexpr_impl(std::forward<Args&&>(args)...);
    }
}

#endif
