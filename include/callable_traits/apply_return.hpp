/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_APPLY_RETURN_HPP
#define CALLABLE_TRAITS_APPLY_RETURN_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct apply_return_error : sfinae_error {

            static_assert(Sfinae,
                "callable_traits::apply_return<T, R> is "
                "not a meaningful operation for this T.");
        };

        template<typename T, typename R>
        struct apply_return_helper {
            using type = typename detail::traits<T>::template apply_return<R>;
        };

        //special case
        template<typename... Args, typename R>
        struct apply_return_helper<std::tuple<Args...>, R> {
            using type = R(Args...);
        };
    }

    template<typename T, typename R>
    struct apply_return {

        using type = detail::fail_if_invalid<
            typename detail::apply_return_helper<T, R>::type,
            detail::apply_return_error<true>>;
    };

    template<typename T, typename R>
    using apply_return_t = typename apply_return<T, R>::type;
}

#endif
