/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_APPLY_RETURN_HPP
#define CALLABLE_TRAITS_APPLY_RETURN_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct apply_return_error {

            static_assert(Sfinae,
                "callable_traits::apply_return<T> is "
                "not a meaningful operation for this T.");
        };
    }

    namespace permissive {

        template<typename T, typename R>
        using apply_return = detail::fallback_if_invalid<
            typename detail::traits<T>::template apply_return<R>,
            T>;
    }

    namespace verbose {

        template<typename T, typename R>
        using apply_return = detail::fail_if_invalid<
            typename detail::traits<T>::template apply_return<R>,
            detail::apply_return_error<false>>;
    }

    template<typename T, typename R>
    using apply_return = detail::fail_if_invalid<
        typename detail::traits<T>::template apply_return<R>,
        detail::apply_return_error<true>>;
}

#endif
