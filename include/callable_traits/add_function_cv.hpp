/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_FUNCTION_CV_HPP
#define CALLABLE_TRAITS_ADD_FUNCTION_CV_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct add_function_cv_error {

            static_assert(Sfinae,
                "callable_traits::add_function_cv<T> "
                "is not a meaningful operation for this T.");
        };
    }

    namespace permissive {

        template<typename T>
        using add_function_cv = detail::fallback_if_invalid<
            typename detail::traits<T>::add_function_cv,
            T>;
    }

    namespace verbose {

        template<typename T>
        using add_function_cv = detail::fail_if_invalid<
            typename detail::traits<T>::add_function_cv,
            detail::add_function_cv_error<false>>;
    }

    template<typename T>
    using add_function_cv = detail::fail_if_invalid<
        typename detail::traits<T>::add_function_cv,
        detail::add_function_cv_error<true>>;
}

#endif
