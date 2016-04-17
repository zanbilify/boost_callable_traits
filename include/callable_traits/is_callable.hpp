/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_CALLABLE_HPP
#define CALLABLE_TRAITS_IS_CALLABLE_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/min_arity.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    template<typename T>
    static constexpr inline auto
    is_callable() {
        return std::integral_constant<bool, min_arity<T>().value >= 0>{};
    }

    template<typename T>
    static constexpr inline auto
    is_callable(T&&) {
        return is_callable<T&&>();
    }
}

#endif //CALLABLE_TRAITS_IS_CALLABLE_HPP
