/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_QUALIFIER_TRAITS_HPP
#define CALLABLE_TRAITS_QUALIFIER_TRAITS_HPP

namespace callable_traits {

    namespace ctdetail {

        template<typename T>
        class qualifier_traits {

        protected:

            static constexpr flags cv_flags = cv_of<T>::value;
            static constexpr flags ref_flags = ref_of<T>::value;
            static constexpr flags q_flags = cv_flags | ref_flags;

        public:

            static constexpr bool is_reference_qualified = ref_flags > 0;
            static constexpr bool is_lvalue_reference_qualified = ref_flags == lref_;
            static constexpr bool is_rvalue_reference_qualified = ref_flags == rref_;
            static constexpr bool is_const_qualified = (cv_flags & const_) > 0;
            static constexpr bool is_volatile_qualified = (cv_flags & volatile_) > 0;
            static constexpr bool is_cv_qualified = cv_flags == (const_ | volatile_);
        };
    }
}

#endif