/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_CONSTEXPR_HPP
#define CALLABLE_TRAITS_IS_CONSTEXPR_HPP

#include <callable_traits/detail/is_constexpr_impl.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/required_definitions.hpp>
#include <utility>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    is_constexpr(T&& t){

        return detail::is_constexpr_impl(
            ::std::forward<T>(t),
            detail::is_constexpr_constructible<T>{}
        );
    }

    template<typename T>
    inline constexpr auto
    is_constexpr(){

        using result_type =
            decltype(is_constexpr(std::declval<T>()));

        return result_type{};
    }
}

#endif
