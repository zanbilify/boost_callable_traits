/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_PUSH_FRONT_HPP
#define CALLABLE_TRAITS_PUSH_FRONT_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct push_front_error {

            static_assert(Sfinae,
                "callable_traits::push_front<T, Args...> is "
                "not a meaningful operation for this T.");
        };
    }

    namespace permissive {

        template<typename T, typename... Args>
        using push_front = detail::fallback_if_invalid<
            typename detail::traits<T>::template push_front<Args...>,
            T>;
    }

    namespace verbose {

        template<typename T, typename... Args>
        using push_front = detail::fail_if_invalid<
            typename detail::traits<T>::template push_front<Args...>,
            detail::push_front_error<false>>;
    }

    template<typename T, typename... Args>
    using push_front = detail::fail_if_invalid<
        typename detail::traits<T>::template push_front<Args...>,
        detail::push_front_error<true>>;
}

#endif //CALLABLE_TRAITS_PUSH_FRONT_HPP
