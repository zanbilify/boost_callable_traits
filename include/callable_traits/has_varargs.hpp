/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_VARARGS_HPP
#define CALLABLE_TRAITS_HAS_VARARGS_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    has_varargs() {
        return typename detail::traits<T>::has_varargs{};
    }

    template<typename T>
    inline constexpr auto
    has_varargs(T&&) {
        using no_ref = typename std::remove_reference<T>::type;
        return has_varargs<no_ref>();
    }
}

#endif
