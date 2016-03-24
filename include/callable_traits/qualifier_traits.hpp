/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_QUALIFIER_TRAITS_HPP
#define CALLABLE_TRAITS_QUALIFIER_TRAITS_HPP

#include <type_traits>

namespace callable_traits {

    namespace ctdetail {

        template<typename T>
        class qualifier_traits {

        protected:

            static constexpr flags cv_flags = cv_of<T>::value;
            static constexpr flags ref_flags = ref_of<T>::value;
            static constexpr flags q_flags = cv_flags | ref_flags;

        public:

            using is_reference_qualified = std::integral_constant<bool, 0 < ref_flags>;
            using is_lvalue_reference_qualified = std::integral_constant<bool, ref_flags == lref_>;
            using is_rvalue_reference_qualified = std::integral_constant<bool, ref_flags == rref_>;
            using is_const_qualified = std::integral_constant<bool, 0 < (cv_flags & const_)>;
            using is_volatile_qualified = std::integral_constant<bool, 0 < (cv_flags & volatile_)>;
            using is_cv_qualified = std::integral_constant<bool, cv_flags == (const_ | volatile_)>;
        };
    }
}

#endif