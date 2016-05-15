/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_add_member_volatile_HPP
#define CALLABLE_TRAITS_add_member_volatile_HPP

#include <callable_traits/detail/required_definitions.hpp>


namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct add_member_volatile_error {

            static_assert(Sfinae,
                "callable_traits::add_member_volatile<T> "
                "is not a meaningful operation for this T.");
        };
    }

    template<typename T>
    using add_member_volatile = detail::fail_if_invalid<
        typename detail::traits<T>::add_member_volatile,
        detail::add_member_volatile_error<true>>;
}

#endif
