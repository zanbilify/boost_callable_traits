/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_MEMBER_QUALIFIERS_HPP
#define CALLABLE_TRAITS_HAS_MEMBER_QUALIFIERS_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    template<typename T>
    inline constexpr auto
    has_member_qualifiers() {
        return typename detail::traits<T>::has_member_qualifiers{};
    }
    
    template<typename T>
    inline constexpr auto
    has_member_qualifiers(T&&) {
        using no_ref = typename std::remove_reference<T>::type;
        return typename detail::traits<no_ref>::has_member_qualifiers{};
    }
}

#endif //CALLABLE_TRAITS_HAS_MEMBER_QUALIFIERS_HPP
