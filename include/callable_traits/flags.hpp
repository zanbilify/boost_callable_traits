/*!
@file
Defines `flags`

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FLAGS_HPP
#define CALLABLE_TRAITS_FLAGS_HPP

namespace callable_traits {

    namespace ctdetail {

        //! flags are bit flags used to signify cv-qualifiers
        //! and ref-qualifiers/reference types
        using flags = std::uint32_t;

        /*
        This grid is useful for debugging type errors where
        the error messages often include a `flags` value:

        value | RR LR V  C | result
        --------------------------------------------
        0   | 0  0  0  0 | default
        1   | 0  0  0  1 | const
        2   | 0  0  1  0 | volatile
        3   | 0  0  1  1 | const volatile
        --------------------------------------------
        4   | 0  1  0  0 | lref
        5   | 0  1  0  1 | const lref
        6   | 0  1  1  0 | volatile lref
        7   | 0  1  1  1 | const volatile lref
        --------------------------------------------
        8   | 1  0  0  0 | rref
        9   | 1  0  0  1 | const rref
        10   | 1  0  1  0 | volatile rref
        11   | 1  0  1  1 | const volatile rref
        --------------------------------------------
        12+  | 1  1  *  * | invalid - use `collapse`

        */

        constexpr flags max_flags_value = 11;

        //! Flag representing the default qualifiers on a type 
        //! or member function overload.
        constexpr flags default_ = 0;

        //! Flag representing a const qualifier on a type or
        //! member function overload.
        constexpr flags const_ = 1;

        //! Flag representing a volatile qualifier on a type
        //! or member function overload.
        constexpr flags volatile_ = 2;

        //! Flag representing an lvalue reference type, or
        //! an lvalue-reference-qualified member function
        //! overload.
        constexpr flags lvalue_reference_ = 4;

        //! shorthand for `lvalue_reference_`.
        constexpr flags lref_ = 4;

        //! shorthand for `const_ | lvalue_reference_`.
        constexpr flags clref_ = 5;

        //! Flag representing an lvalue reference type, or
        //! an rvalue-reference-qualified member function
        //! overload.
        constexpr flags rvalue_reference_ = 8;

        //! shorthand for `rvalue_reference_`.
        constexpr flags rref_ = 8;

        constexpr flags cv_ = 3;

        template<flags Flags>
        using add_const = std::integral_constant<flags, Flags | const_>;

        template<flags Flags>
        using remove_const = std::integral_constant<flags, Flags & ~const_>;

        template<flags Flags>
        using is_const = std::integral_constant<bool,
            (Flags & const_) != 0
        >;

        template<flags Flags>
        using add_volatile = std::integral_constant<flags, Flags | volatile_>;

        template<flags Flags>
        using remove_volatile = std::integral_constant<flags, Flags & ~volatile_>;

        template<flags Flags>
        using is_volatile = std::integral_constant<bool,
            (Flags & volatile_) != 0
        >;

        template<flags Flags>
        using add_cv = std::integral_constant<flags, Flags | volatile_ | const_>;

        template<flags Flags>
        using remove_cv = std::integral_constant<flags, Flags & ~volatile_ & ~const_>;

        template<flags Flags>
        using remove_reference = std::integral_constant<flags, (Flags & ~rref_) & ~lref_>;

        template<flags Flags>
        using is_lvalue_reference = std::integral_constant<bool, (Flags & lref_) != 0>;

        //is_rvalue_reference uses reference collapsing rules
        template<flags Flags>
        using is_rvalue_reference = std::integral_constant<bool, (Flags & (lref_ | rref_)) == rref_>;

        template<flags Flags>
        using force_lvalue_reference = std::integral_constant<flags, (Flags & ~rref_) | lref_>;

        template<flags Flags>
        using force_rvalue_reference = std::integral_constant<flags, (Flags & ~lref_) | rref_>;

        template<flags Existing, flags Other>
        using collapse = std::integral_constant<flags,
            (Existing & lref_) == 0 ?
            (Existing | Other)
            : (Existing | (Other & ~rref_))
        >;

        template<flags Flags>
        using add_lvalue_reference = std::integral_constant<flags, lref_ | (Flags & ~rref_)>;

        template<flags Flags>
        using add_rvalue_reference = collapse<Flags, rref_>;

        template<flags Flags>
        using guarantee_reference = std::integral_constant<flags,
            (
                (Flags & rref_) == 0
                && (Flags & lref_) == 0
                ) ?
            (Flags | lref_) : Flags
        >;

        template<typename U, typename T = typename std::remove_reference<U>::type>
        using cv_of = std::integral_constant<flags,
            (std::is_const<T>::value ? const_ : default_)
            | (std::is_volatile<T>::value ? volatile_ : default_)
        >;

        using force_ref = std::true_type;

        template<typename T, typename ForceRef = std::false_type>
        using ref_of = std::integral_constant<flags,
            std::is_rvalue_reference<T>::value ? rref_
            : (std::is_lvalue_reference<T>::value ? lref_
                : (ForceRef::value ? lref_ : default_))
        >;
    }
}
#endif