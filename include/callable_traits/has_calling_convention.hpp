/*!
@file add_member_const

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_CALLING_CONVENTION_HPP
#define CALLABLE_TRAITS_HAS_CALLING_CONVENTION_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/calling_conventions.hpp>
#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T, typename Tag>
    inline constexpr auto
    has_calling_convention() {
        return typename detail::has_calling_convention_t<T, Tag>::type{};
    }

    template<typename T, typename Tag>
    inline constexpr auto
    has_calling_convention(T&&) {
        using no_ref = typename std::remove_reference<T>::type;
        return has_calling_convention<no_ref, Tag>();
    }
}

#endif //CALLABLE_TRAITS_HAS_CALLING_CONVENTION_HPP
