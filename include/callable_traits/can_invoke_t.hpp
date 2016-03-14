/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CAN_INVOKE_T_HPP
#define CALLABLE_TRAITS_CAN_INVOKE_T_HPP

#include <callable_traits/test_invoke.hpp>
#include <callable_traits/substitution.hpp>
#include <callable_traits/normalize_reference.hpp>
#include <type_traits>

namespace callable_traits {

    namespace ctdetail {

        template<typename Dispatch, typename... Args>
        struct can_invoke_t {
            
            using callable = typename Dispatch::type;
            using class_type = typename Dispatch::class_type;

            using invoke_t = typename std::conditional<
                std::is_same<class_type, invalid_type>::value,
                test_invoke<Dispatch, Args...>,
                test_invoke<Dispatch, class_type, Args...>
            >::type;

            static constexpr bool value =
                !std::is_same<
                    substitution_failure,
                    decltype(invoke_t{}(
                        std::declval<callable>(),
                        std::declval<Args>()...
                ))>::value
                || !std::is_same<
                    substitution_failure,
                    decltype(invoke_t{}(
                        std::declval<callable>(),
                        std::declval<typename Dispatch::invoke_type>(),
                        std::declval<Args>()...
                ))>::value;

            static constexpr int arg_count = invoke_t::arg_count;
        };

        template<typename Dispatch>
        struct can_invoke_t<Dispatch, void> {

            using callable = typename Dispatch::type;
            using class_type = typename Dispatch::class_type;

            using invoke_t = typename std::conditional<
                std::is_same<class_type, invalid_type>::value,
                test_invoke<Dispatch>,
                test_invoke<Dispatch, class_type>
            >::type;

            static constexpr bool value =
                !std::is_same<
                substitution_failure,
                decltype(invoke_t{}(
                    std::declval<callable>()
                ))>::value
                || !std::is_same<
                substitution_failure,
                decltype(invoke_t{}(
                    std::declval<callable>(),
                    std::declval<typename Dispatch::invoke_type>()
                ))>::value;

            static constexpr int arg_count = 0;
        };
    }
}

#endif