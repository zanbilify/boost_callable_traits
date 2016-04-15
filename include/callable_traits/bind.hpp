/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_BIND_HPP
#define CALLABLE_TRAITS_BIND_HPP

#include <callable_traits/detail/bind_expression.hpp>
#include <callable_traits/detail/bind_expression_parser.hpp>
#include <callable_traits/detail/required_definitions.hpp>
#include <utility>

namespace callable_traits {

#ifdef CALLABLE_TRAITS_MSVC

template<bool MsvcAllowed = false, typename... T>
inline constexpr int
bind(T&&...) {

    static_assert(MsvcAllowed,
        "The native Microsoft Visual C++ compiler cannot "
        "compile callable_traits::bind. To use this feature "
        "in Windows, compile with Clang-cl or MinGW instead.");

    return -1;
}

#else

    template<typename T, typename... Args>
    inline constexpr auto
    bind(T&& t, Args&&... args) ->
        detail::bind_expression<T&&, Args&&...> {

        return {
            ::std::forward<T>(t),
            ::std::forward<Args>(args)...
        };
    }

#endif //#ifdef CALLABLE_TRAITS_MSVC

}

#endif
