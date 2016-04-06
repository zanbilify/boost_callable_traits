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
#include <utility>

namespace callable_traits {

    template<typename T, typename... Args>
    inline constexpr auto
    bind(T&& t, Args&&... args) -> detail::bind_expression<T&&, Args&&...> {
        return {::std::forward<T>(t), ::std::forward<Args>(args)...};
    }
}

#endif
