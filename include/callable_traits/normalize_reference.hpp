/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_NORMALIZE_REFERENCE_HPP
#define CALLABLE_TRAITS_NORMALIZE_REFERENCE_HPP

#include <functional>
#include <type_traits>
#include <utility>

namespace callable_traits {

    namespace ctdetail {

        template<typename T, typename = std::true_type>
        struct is_reference_wrapper {
            using type = std::false_type;
        };

        template<typename T>
        struct is_reference_wrapper_helper;

        template<typename T>
        struct is_reference_wrapper_helper<std::reference_wrapper<T>> {
            using type = std::true_type;
        };

        template<typename T>
        struct is_reference_wrapper<T, 
            typename is_reference_wrapper_helper<
                typename std::remove_cv<typename std::remove_reference<T>::type>::type
        >::type> {
            using type = std::true_type;
        };

        template<typename T, typename = std::true_type>
        struct normalize_reference_t {
            using type = T;
        };

        template<typename T>
        struct normalize_reference_t<T, can_dereference<T>>{
            using type = decltype(*std::declval<T>());
        };

        template<typename T>
        struct normalize_reference_t<T, typename is_reference_wrapper<T>::type> {
            using type = decltype(std::declval<T>().get());
        };

        // normalize_reference expects a pointer, a reference, or a reference_wrapper.
        // When T is a pointer, normalize_reference<T> is the resulting type
        // of the pointer dereferenced. When T is an std::reference_wrapper,
        // normalize_reference<T> is the underlying reference type.

        template<typename T>
        using normalize_reference = typename normalize_reference_t<T>::type;
    }
}

#endif