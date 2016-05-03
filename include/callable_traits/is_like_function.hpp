/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_LIKE_FUNCTION_HPP
#define CALLABLE_TRAITS_IS_LIKE_FUNCTION_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    template<typename T>
    inline constexpr auto is_like_function() {
        return std::integral_constant<bool,
            detail::function<T, detail::decay_if_ptr_or_integral_constant<T>>::value>{};
    }

    template<typename T>
    inline constexpr auto is_like_function(T&&) {
        return is_like_function<T&&>();
    }
}

#endif // CALLABLE_TRAITS_IS_LIKE_FUNCTION_HPP

