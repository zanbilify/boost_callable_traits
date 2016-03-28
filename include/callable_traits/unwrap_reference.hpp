/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_UNWRAP_REFERENCE_HPP
#define CALLABLE_TRAITS_UNWRAP_REFERENCE_HPP

#include <callable_traits/is_reference_wrapper.hpp>
#include <type_traits>

namespace callable_traits {

    namespace detail {

        template<typename T, typename = std::true_type>
        struct unwrap_reference_t {
            using type = T;
        };

        template<typename T>
        struct unwrap_reference_t<T, is_reference_wrapper<T>> {
            using type = decltype(std::declval<T>().get());
        };

        template<typename T>
        using unwrap_reference = typename unwrap_reference_t<T>::type;
    }
}

#endif