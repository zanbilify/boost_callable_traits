/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_LIKE_FUNCTION_HPP
#define CALLABLE_TRAITS_IS_LIKE_FUNCTION_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T>
    inline constexpr auto is_like_function() {
        return detail::bool_type<detail::function<T>::value>{};
    }

    template<typename T>
    inline constexpr auto is_like_function(T&&) {
        using no_ref = typename std::remove_reference<T>::type;
        return is_like_function<no_ref>();
    }
}

#endif // CALLABLE_TRAITS_IS_LIKE_FUNCTION_HPP

