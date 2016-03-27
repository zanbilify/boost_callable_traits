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
#include <type_traits>

namespace callable_traits {

    namespace ctdetail {

        template<typename Dispatch, typename... Args>
        struct can_invoke_t {
            
            using callable = typename Dispatch::type;
            using class_type = typename Dispatch::class_type;
            using is_member_pointer = typename Dispatch::is_member_pointer;

            using invoker = typename std::conditional<
                is_member_pointer::value,
                test_invoke<Dispatch, class_type, Args...>,
                test_invoke<Dispatch, Args...>
            >::type;

            using test = typename std::conditional<
                is_member_pointer::value,
                decltype(invoker{}(
                    std::declval<callable>(),
                    std::declval<typename Dispatch::invoke_type>(),
                    std::declval<Args>()...
                )),
                decltype(invoker{}(
                    std::declval<callable>(),
                    std::declval<Args>()...
                ))
            >::type;

            static constexpr bool value =
                !std::is_same<substitution_failure, test>{};
                
            static constexpr int arg_count = invoker::arg_count;
        };

        template<typename Dispatch>
        struct can_invoke_t<Dispatch, void> {

            using callable = typename Dispatch::type;
            using class_type = typename Dispatch::class_type;
            using is_member_pointer = typename Dispatch::is_member_pointer;

            using invoker = typename std::conditional<
                is_member_pointer::value,
                test_invoke<Dispatch>,
                test_invoke<Dispatch, class_type>
            >::type;

            using invoke_type = typename Dispatch::invoke_type;

            using test = typename std::conditional<
                is_member_pointer::value,
                decltype(invoker{}(
                    std::declval<callable>(),
                    std::declval<invoke_type>()
                )),
                decltype(invoker{}(std::declval<callable>()))
            >::type;

            static constexpr bool value =
                !std::is_same<substitution_failure, test>::value;

            static constexpr int arg_count = 0;
        };
    }
}

#endif
