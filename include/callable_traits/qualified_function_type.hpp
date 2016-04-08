/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_QUALIFIED_FUNCTION_TYPE_HPP
#define CALLABLE_TRAITS_QUALIFIED_FUNCTION_TYPE_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct qualified_function_type_error {

            static_assert(Sfinae,
                "Unable to determine the qualified function type for "
                "type T in callable_traits::qualified_function_type<T>.");
        };
    }

    namespace permissive {

        template<typename T>
        using qualified_function_type = detail::fallback_if_invalid<
            typename detail::traits<T>::qualified_function_type,
            T>;
    }

    namespace verbose {

        template<typename T>
        using qualified_function_type = detail::fail_if_invalid<
            typename detail::traits<T>::qualified_function_type,
            detail::qualified_function_type_error<false>>;
    }

    template<typename T>
    using qualified_function_type = detail::fail_if_invalid<
        typename detail::traits<T>::qualified_function_type,
        detail::qualified_function_type_error<true>>;
}

#endif
