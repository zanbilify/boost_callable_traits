/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_SAME_QUALIFIERS_HPP
#define CALLABLE_TRAITS_HAS_SAME_QUALIFIERS_HPP

#include <callable_traits/detail/core.hpp>
#include <callable_traits/copy_qualifiers.hpp>

namespace callable_traits {

    
    template<typename T, typename Callable>
    inline constexpr auto
    has_same_qualifiers() {
        return typename std::is_same<T, copy_qualifiers<T, Callable>>::type{};
    }

    template<typename T, typename Callable>
    inline constexpr auto
    has_same_qualifiers(T&&, Callable&&) {
        return has_same_qualifiers<T&&, Callable&&>();
    }
    
}

#endif //#ifndef CALLABLE_TRAITS_COPY_QUALIFIERS_HPP
