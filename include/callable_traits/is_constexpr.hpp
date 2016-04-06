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
#include <utility>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    is_constexpr(T&& t){
        using can_construct = detail::is_constexpr_constructible<T>;
        return detail::is_constexpr_impl(std::forward<T>(t), can_construct{});
    }

    template<typename T>
    inline constexpr auto
    is_constexpr(){
        return decltype(is_constexpr(std::declval<T>())){};
    }
}

#endif
