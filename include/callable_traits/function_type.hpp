/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FUNCTION_TYPE_HPP
#define CALLABLE_TRAITS_FUNCTION_TYPE_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    namespace detail {

        template<typename T, bool IsValid = traits<T>::value>
        struct make_function {
            using type = T;
        };

        template<typename T>
        struct make_function<T, false> {
            using type = T();
        };
    }

    template<typename T>
    struct function_type {

        using type = detail::fallback_if_invalid<
            typename detail::traits<T>::function_type,
            typename detail::make_function<T>::type>;
    };

    template<typename T>
    using function_type_t = typename function_type<T>::type;
}

#endif
