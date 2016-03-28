/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_GENERAL_HPP
#define CALLABLE_TRAITS_GENERAL_HPP

#include <callable_traits/can_dereference.hpp>
#include <type_traits>
#include <memory>


namespace callable_traits {

    namespace detail {

        template<typename T, typename = std::true_type>
        struct general;

        template<typename T>
        struct general<T, cannot_dereference_to_class<typename std::remove_reference<T>::type>> {
            using type = typename std::remove_reference<T>::type;
            using original_type = T;
        };

        template<typename T>
        struct general<T, can_dereference_to_class<typename std::remove_reference<T>::type>> {
            using type = typename std::remove_reference<decltype(*std::declval<T>())>::type;
            using original_type = T;
        };
    }
}

#endif