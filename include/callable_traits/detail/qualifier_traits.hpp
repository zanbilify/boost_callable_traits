/*!
@file
Defines `flags`

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_QUALIFIER_TRAITS_HPP
#define CALLABLE_TRAITS_DETAIL_QUALIFIER_TRAITS_HPP

#include <callable_traits/detail/qualifier_flags.hpp>

#include <type_traits>
#include <cstdint>

namespace callable_traits {

namespace detail {

        template<typename T>
        struct qualifier_traits {

            static constexpr flags cv_flags = cv_of<T>::value;
            static constexpr flags ref_flags = ref_of<T>::value;
            static constexpr flags q_flags = cv_flags | ref_flags;

            using has_member_qualifiers = std::integral_constant<bool, q_flags != default_>;
            using is_const_member = std::integral_constant<bool, 0 < (cv_flags & const_)>;
            using is_volatile_member = std::integral_constant<bool, 0 < (cv_flags & volatile_)>;
            using is_cv_member = std::integral_constant<bool, cv_flags == (const_ | volatile_)>;

#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

            using is_reference_member = std::false_type;
            using is_lvalue_reference_qualified = std::false_type;
            using is_rvalue_reference_qualified = std::false_type;
#else
            using is_reference_member = std::integral_constant<bool, 0 < ref_flags>;
            using is_lvalue_reference_member = std::integral_constant<bool, ref_flags == lref_>;
            using is_rvalue_reference_member = std::integral_constant<bool, ref_flags == rref_>;

#endif //#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

        };
    }
}

#endif //#ifndef CALLABLE_TRAITS_DETAIL_QUALIFIER_TRAITS_HPP
