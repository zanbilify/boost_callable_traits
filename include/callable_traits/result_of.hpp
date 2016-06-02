/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_RESULT_OF_HPP
#define CALLABLE_TRAITS_RESULT_OF_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct result_of_error : sfinae_error {

            static_assert(Sfinae,
                "callable_traits::result_of<T> is not "
                "a meaningful operation for this T.");
        };
    }

    template<typename T>
    struct result_of {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::return_type,
            detail::result_of_error<true>>;
    };

    template<typename T>
    using result_of_t = typename result_of<T>::type;
}

#endif
