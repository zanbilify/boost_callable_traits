/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_GENERALIZED_CLASS_HPP
#define CALLABLE_TRAITS_DETAIL_GENERALIZED_CLASS_HPP

#include <callable_traits/detail/can_dereference.hpp>
#include <type_traits>
#include <memory>


namespace callable_traits {

    namespace detail {

        template<typename T>
        struct is_class_after_dereference
        {
            template<typename>
            struct check {};

            template<typename U, typename K = typename std::enable_if<!std::is_function<typename std::remove_reference<U>::value>::value, U>::type>
            static typename std::enable_if<
                std::is_class<
                    typename std::remove_reference<decltype(*std::declval<K>())>::type
                >::value,
                std::int8_t
            >::type test(std::nullptr_t);

            template<typename>
            static std::int16_t test(...);

            static constexpr const bool value =
                sizeof(test<T>(nullptr)) == sizeof(std::int8_t);
        };

        template<typename T>
        using can_dereference_to_class = std::integral_constant<bool,
            is_class_after_dereference<T>::value
        >;

        template<typename T>
        using cannot_dereference_to_class = std::integral_constant<bool,
            !is_class_after_dereference<T>::value
        >;
        
        template<typename T, typename = std::true_type>
        struct generalized_class;

        template<typename T>
        struct generalized_class<T, cannot_dereference_to_class<typename std::remove_reference<T>::type>> {
            using type = typename std::remove_reference<T>::type;
            using original_type = T;
        };

        template<typename T>
        struct generalized_class<T, can_dereference_to_class<typename std::remove_reference<T>::type>> {
            using type = typename std::remove_reference<decltype(*std::declval<T>())>::type;
            using original_type = T;
        };
    }
}

#endif