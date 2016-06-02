/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_MEMBER_VOLATILE_HPP
#define CALLABLE_TRAITS_REMOVE_MEMBER_VOLATILE_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct remove_member_volatile_error : sfinae_error {

            static_assert(Sfinae,
                "callable_traits::remove_member_volatile<T> "
                "is not a meaningful operation for this T.");
        };
    }

    template<typename T>
    struct remove_member_volatile {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::remove_member_volatile,
            detail::remove_member_volatile_error<true>>;
    };

    template<typename T>
    using remove_member_volatile_t =
        typename remove_member_volatile<T>::type;
}

#endif
