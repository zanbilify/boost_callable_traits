#ifndef CALLABLE_TRAITS_DETAIL_CAN_INVOKE_CONSTEXPR_T_HPP
#define CALLABLE_TRAITS_DETAIL_CAN_INVOKE_CONSTEXPR_T_HPP

#include <callable_traits/detail/test_invoke.hpp>
#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>

#include <type_traits>

namespace callable_traits {

    namespace detail {

        template<typename T, typename... Args,
            typename std::enable_if<!detail::conjunction<
                is_constexpr_constructible<T>,
                is_constexpr_constructible<Args>...
            >::value, int>::type = 0>
        inline constexpr auto
        can_invoke_constexpr_impl(T&&, Args&&...) {
            return std::false_type{};
        }

        template<typename T, typename... Args,
                 typename std::enable_if<detail::conjunction<
                     is_constexpr_constructible<T>,
                     is_constexpr_constructible<Args>...
                 >::value, int>::type = 0>
        inline constexpr auto
        can_invoke_constexpr_impl(T&& t, Args&&... args) {
            using traits = detail::traits<T&&>;
            using test = detail::test_invoke_constexpr<traits, Args&&...>;
            using result = decltype(test{}(::std::forward<T>(t), ::std::forward<Args>(args)...));
            using failure = detail::substitution_failure;
            using is_invalid_invoke = std::is_same<result, failure>;
            return std::integral_constant<bool, !is_invalid_invoke::value>{};
        }
    }
}
#endif // CALLABLE_TRAITS_DETAIL_CAN_INVOKE_CONSTEXPR_T_HPP

