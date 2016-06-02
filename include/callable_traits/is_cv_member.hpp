/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_CV_MEMBER_HPP
#define CALLABLE_TRAITS_IS_CV_MEMBER_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    is_cv_member() {
        return typename detail::traits<T>::is_cv_member{};
    }

    template<typename T>
    inline constexpr auto
    is_cv_member(T&&) {
        using no_ref = typename std::remove_reference<T>::type;
        return is_cv_member<no_ref>();
    }
}

#endif
