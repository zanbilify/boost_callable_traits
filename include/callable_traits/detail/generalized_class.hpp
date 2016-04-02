/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_GENERALIZED_CLASS_HPP
#define CALLABLE_TRAITS_DETAIL_GENERALIZED_CLASS_HPP

#include <callable_traits/detail/utility.hpp>
#include <type_traits>
#include <memory>


namespace callable_traits {

    namespace detail {

        template<typename T>
        struct can_make_reference {

            template<typename U>
            static dummy test(typename std::remove_reference<U&>::type*);

            template<typename>
            static void test(...);

            using type = decltype(can_make_reference::test<T>(nullptr));
            static constexpr bool value = std::is_same<dummy, type>::value;
        };

        template<typename T>
        struct is_class_after_dereference
        {
            template<typename>
            struct check {};

            template<typename U,
                typename K = typename std::enable_if<can_make_reference<U>::value, U>::type,
                typename Dereferenced = decltype(*std::declval<K>()),
                typename C = typename std::remove_reference<Dereferenced>::type,
                typename std::enable_if<std::is_class<C>::value, int>::type = 0>
            static std::int8_t test(int);

            template<typename>
            static std::int16_t test(...);

            static constexpr const bool value =
                sizeof(test<T>(0)) == sizeof(std::int8_t);
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
