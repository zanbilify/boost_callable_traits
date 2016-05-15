#ifndef CALLABLE_TRAITS_DETAIL_CAN_INVOKE_IMPL_HPP
#define CALLABLE_TRAITS_DETAIL_CAN_INVOKE_IMPL_HPP

#include <callable_traits/detail/test_invoke.hpp>
#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <type_traits>

namespace callable_traits {

    namespace detail {

        template<typename T, typename... Args>
        inline constexpr auto
        can_invoke_impl(T&& t, Args&&... args) {
            using traits = detail::traits<T&&>;
            using test = detail::test_invoke<traits, Args&&...>;
            using result = decltype(test{}(::std::forward<T>(t), ::std::forward<Args>(args)...));
            using failure = detail::substitution_failure;
            using is_invalid_invoke = std::is_same<result, failure>;
            return std::integral_constant<bool, !is_invalid_invoke::value>{};
        }

        template<typename T, typename... Args>
        inline constexpr auto
        can_invoke_impl() {
            using traits = detail::traits<T>;
            using test = detail::test_invoke<traits, Args...>;
            using result = decltype(test{}(::std::declval<T>(), ::std::declval<Args>()...));
            using failure = detail::substitution_failure;
            using is_invalid_invoke = std::is_same<result, failure>;
            return std::integral_constant<bool, !is_invalid_invoke::value>{};
        }
    }
}

#endif // CALLABLE_TRAITS_DETAIL_CAN_INVOKE_IMPL_HPP

