/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARITY_HPP
#define CALLABLE_TRAITS_ARITY_HPP

#include <callable_traits/detail/arity.hpp>
#include <callable_traits/detail/traits.hpp>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    arity(T&&) {
        return detail::arity_t<detail::traits<T&&>>{};
    }

    template<typename T>
    inline constexpr auto
    arity() {
        return detail::arity_t<detail::traits<T>>{};
    }
}

#endif
