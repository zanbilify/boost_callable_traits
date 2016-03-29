 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_IS_INTEGRAL_CONSTANT_HPP
#define CALLABLE_TRAITS_DETAIL_IS_INTEGRAL_CONSTANT_HPP

#include <callable_traits/detail/shallow_decay.hpp>

#include <type_traits>
#include <utility>

namespace callable_traits {

    namespace detail {
        
        template<typename T>
        struct is_integral_constant_t {
            static constexpr bool value = false;
        };

        template<typename T, T Value>
        struct is_integral_constant_t<std::integral_constant<T, Value>> {
            static constexpr bool value = true;
        };

        template<typename T>
        using is_integral_constant = std::integral_constant<bool,
            is_integral_constant_t<shallow_decay<T>>::value>;
    }
}

#endif
