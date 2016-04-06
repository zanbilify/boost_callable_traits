/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_VOID_RETURN_HPP
#define CALLABLE_TRAITS_HAS_VOID_RETURN_HPP

#include <callable_traits/result_of.hpp>
#include <type_traits>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    has_void_return(T&&) {
        return typename std::is_same<result_of<T&&>, void>::type{};
    }

    template<typename T>
    inline constexpr auto
    has_void_return() {
        return typename std::is_same<result_of<T>, void>::type{};
    }
}

#endif
