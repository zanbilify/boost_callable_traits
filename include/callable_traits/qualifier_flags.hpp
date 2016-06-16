/*!
@file
Defines `flags`

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_QUALIFIER_FLAGS_HPP
#define CALLABLE_TRAITS_QUALIFIER_FLAGS_HPP

#include <type_traits>
#include <cstdint>

namespace callable_traits {

        //bit flags used to signify cv/ref qualifiers
        using flags = std::uint32_t;

        /*

            | && &  V  C |
        --------------------------------------------
        0   | 0  0  0  0 | default
        1   | 0  0  0  1 | const
        2   | 0  0  1  0 | volatile
        3   | 0  0  1  1 | const volatile
        --------------------------------------------
        4   | 0  1  0  0 | &
        5   | 0  1  0  1 | const &
        6   | 0  1  1  0 | volatile &
        7   | 0  1  1  1 | const volatile &
        --------------------------------------------
        8   | 1  0  0  0 | &&
        9   | 1  0  0  1 | const &&
        10  | 1  0  1  0 | volatile &&
        11  | 1  0  1  1 | const volatile &&

        */

    inline namespace qualifier_flags {

        //! Flag representing the default qualifiers on a type 
        //! or member function overload.
        constexpr flags default_ = 0;

        //! Flag representing a const qualifier on a type or
        //! member function overload.
        constexpr flags const_ = 1;

        //! Flag representing a volatile qualifier on a type
        //! or member function overload.
        constexpr flags volatile_ = 2;

#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

        constexpr flags lref_ = default_;
        constexpr flags rref_ = default_;
#else

        //! Flag representing an lvalue reference type, or
        //! an lvalue-reference-qualified member function
        //! overload.
        constexpr flags lref_ = 4;

        //! Flag representing an lvalue reference type, or
        //! an rvalue-reference-qualified member function
        //! overload.
        constexpr flags rref_ = 8;

#endif //#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

        constexpr flags cv_ = 3;
    }

    namespace detail {

        template<flags Flags>
        using remove_const_flag = std::integral_constant<flags, Flags & ~const_>;

        template<flags Flags>
        using is_const = std::integral_constant<bool,
            (Flags & const_) != 0
        >;

        template<flags Flags>
        using remove_volatile_flag = std::integral_constant<flags, Flags & ~volatile_>;

        template<typename U, typename T = typename std::remove_reference<U>::type>
        using cv_of = std::integral_constant<flags,
            (std::is_const<T>::value ? const_ : default_)
            | (std::is_volatile<T>::value ? volatile_ : default_)
        >;

        template<typename T>
        using ref_of = std::integral_constant<flags,
            std::is_rvalue_reference<T>::value ? rref_
            : (std::is_lvalue_reference<T>::value ? lref_
                : default_)
        >;

        //bit-flag implementation of C++11 reference collapsing rules
        template<flags Existing,
                 flags Other,
                 bool AlreadyHasRef = (Existing & (lref_ | rref_)) != 0,
                 bool AlreadyHasLRef = (Existing & lref_) == lref_,
                 bool IsAddingLRef = (Other & lref_) == lref_
        >
        using collapse_flags = std::integral_constant<flags,
            !AlreadyHasRef ? (Existing | Other)
                : (AlreadyHasLRef ? (Existing | (Other & ~rref_))
                    : (IsAddingLRef ? ((Existing & ~rref_) | Other )
                        : (Existing | Other)))>;

        template<typename T> struct flag_map { static constexpr flags value = default_; };
        template<typename T> struct flag_map<T &> { static constexpr flags value = lref_; };
        template<typename T> struct flag_map<T &&> { static constexpr flags value = rref_; };
        template<typename T> struct flag_map<T const> { static constexpr flags value = const_; };
        template<typename T> struct flag_map<T const &> { static constexpr flags value = const_ | lref_; };
        template<typename T> struct flag_map<T const &&> { static constexpr flags value = const_ | rref_; };
        template<typename T> struct flag_map<T volatile> { static constexpr flags value = volatile_; };
        template<typename T> struct flag_map<T volatile &> { static constexpr flags value = volatile_ | lref_; };
        template<typename T> struct flag_map<T volatile &&> { static constexpr flags value = volatile_ | rref_; };
        template<typename T> struct flag_map<T const volatile> { static constexpr flags value = const_ | volatile_; };
        template<typename T> struct flag_map<T const volatile &> { static constexpr flags value = const_ | volatile_ | lref_; };
        template<typename T> struct flag_map<T const volatile &&> { static constexpr flags value = const_ | volatile_ | rref_; };

    }
}

#endif //#ifndef CALLABLE_TRAITS_QUALIFIER_FLAGS_HPP
