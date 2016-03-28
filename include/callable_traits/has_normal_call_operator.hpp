/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_NORMAL_CALL_OPERATOR_HPP
#define CALLABLE_TRAITS_HAS_NORMAL_CALL_OPERATOR_HPP

#include <utility>
#include <cstdint>

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct has_normal_call_operator
        {
            template<typename N, N Value> struct check { check(std::nullptr_t) {} };

            template<typename U>
            static std::int8_t test(check<decltype(&U::operator()), &U::operator()>);

            template<typename>
            static std::int16_t test(...);
                 
            static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(std::int8_t);
            
        };
    }
}

#endif