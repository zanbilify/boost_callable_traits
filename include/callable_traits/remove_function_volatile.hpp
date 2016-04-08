/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_FUNCTION_VOLATILE_HPP
#define CALLABLE_TRAITS_REMOVE_FUNCTION_VOLATILE_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct remove_function_volatile_error {

            static_assert(Sfinae,
                "callable_traits::remove_function_volatile<T> "
                "is not a meaningful operation for this T.");
        };
    }

    namespace permissive {

        template<typename T>
        using remove_function_volatile = detail::fallback_if_invalid<
            typename detail::traits<T>::remove_function_volatile,
            T>;
    }

    namespace verbose {

        template<typename T>
        using remove_function_volatile = detail::fail_if_invalid<
            typename detail::traits<T>::remove_function_volatile,
            detail::remove_function_volatile_error<false>>;
    }

    template<typename T>
    using remove_function_volatile = detail::fail_if_invalid<
            typename detail::traits<T>::remove_function_volatile,
            detail::remove_function_volatile_error<true>>;
}

#endif
