/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CLEAR_ARGS_HPP
#define CALLABLE_TRAITS_CLEAR_ARGS_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct clear_args_error : sfinae_error {

            static_assert(Sfinae,
                "callable_traits::clear_args<T> is "
                "not a meaningful operation for this T.");
        };
    }

    template<typename T>
    struct clear_args {

        using type = detail::fail_if_invalid<
        typename detail::traits<T>::clear_args,
        detail::clear_args_error<true>>;
    };

    template<typename T>
    using clear_args_t = typename clear_args<T>::type;
}

#endif //CALLABLE_TRAITS_CLEAR_ARGS_HPP
