/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_GENERALIZE_HPP
#define CALLABLE_TRAITS_GENERALIZE_HPP

#include <callable_traits/is_reference_wrapper.hpp>
#include <type_traits>
#include <utility>

namespace callable_traits {

    namespace detail {

        template<typename T, typename = std::true_type>
        struct generalize_t {
            using type = T;
        };

        template<typename T>
        struct generalize_t<T, std::integral_constant<bool,
                can_dereference<T>::value && !is_reference_wrapper<T>::value
        >>{
            using type = decltype(*std::declval<T>());
        };

        template<typename T>
        struct generalize_t<T, is_reference_wrapper<T>> {
            using type = decltype(std::declval<T>().get());
        };

        // generalize expects a pointer, a reference, or a reference_wrapper.
        // When T is a pointer, generalize<T> is the resulting type
        // of the pointer dereferenced. When T is an std::reference_wrapper,
        // generalize<T> is the underlying reference type. Otherwise, generalize
        // is T.

        template<typename T>
        using generalize = typename generalize_t<T>::type;
    }
}

#endif
