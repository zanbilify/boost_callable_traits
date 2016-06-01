/*!
@file add_member_const

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_MEMBER_CONST_HPP
#define CALLABLE_TRAITS_ADD_MEMBER_CONST_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct add_member_const_error {

            static_assert(Sfinae,
                "callable_traits::add_member_const<T> "
                "is not a meaningful operation for this T.");
        };
    }

    template<typename T>
    struct add_member_const {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::add_member_const,
            detail::add_member_const_error<true>>;
    };

    template<typename T>
    using add_member_const_t = typename add_member_const<T>::type;
}

#endif
