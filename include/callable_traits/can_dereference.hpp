/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CAN_DEREFERENCE_HPP
#define CALLABLE_TRAITS_CAN_DEREFERENCE_HPP

#include <cstdint>
#include <type_traits>

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct can_dereference_t
        {
            template<typename>
            struct check {};

            template<typename U>
            static std::int8_t test(
                check<typename std::remove_reference<decltype(*std::declval<U>())>::type>*
            );

            template<typename>
            static std::int16_t test(...);

            static constexpr const bool value =
                sizeof(test<T>(nullptr)) == sizeof(std::int8_t);
        };

        template<typename T>
        using can_dereference = std::integral_constant<bool,
            can_dereference_t<T>::value
        >;
    }
}

#endif