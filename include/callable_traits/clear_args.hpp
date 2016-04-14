/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CLEAR_ARGS_HPP
#define CALLABLE_TRAITS_CLEAR_ARGS_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct clear_args_error {

            static_assert(Sfinae,
                "callable_traits::clear_args<T> is "
                "not a meaningful operation for this T.");
        };
    }

    namespace permissive {

        template<typename T>
        using clear_args = detail::fallback_if_invalid<
            typename detail::traits<T>::clear_args,
            T>;
    }

    namespace verbose {

        template<typename T>
        using clear_args = detail::fail_if_invalid<
            typename detail::traits<T>::clear_args,
            detail::clear_args_error<false>>;
    }

    template<typename T>
    using clear_args = detail::fail_if_invalid<
        typename detail::traits<T>::clear_args,
        detail::clear_args_error<true>>;
}

#endif //CALLABLE_TRAITS_CLEAR_ARGS_HPP
