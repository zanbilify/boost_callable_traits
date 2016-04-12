#ifndef CALLABLE_TRAITS_DETAIL_CAN_INVOKE_CONSTEXPR_T_HPP
#define CALLABLE_TRAITS_DETAIL_CAN_INVOKE_CONSTEXPR_T_HPP

#include <callable_traits/detail/test_invoke.hpp>
#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>

#include <type_traits>
#include <cstdint>
#include <utility>

namespace callable_traits {

    namespace detail {

#ifdef CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED

        inline constexpr auto
        can_invoke_constexpr_impl(...) {
            return std::false_type{};
        }

#else

        template<typename...>
        struct test_invoke_constexpr {
            auto operator()(...) const -> substitution_failure;
        };

        template<typename Pmf, typename T, typename... Args>
        struct test_invoke_constexpr<pmf<Pmf>, T, Args...> {

            using class_t = typename pmf<Pmf>::class_type;

            // An arbitrary expression as the left-hand argument to a non-overloaded
            // comma operator expression that is passed as a template value argument
            // will trigger a substitution failure when the expression is not constexpr
            template<typename P, typename U, typename... Rgs,
                //generalize_if_dissimilar is used to abstract away the rules of INVOKE.
                typename Obj = generalize_if_dissimilar<class_t, U&&>>
            auto operator()(P&& p, U&& u, Rgs&&... rgs) const -> if_integral_constant<P,
                std::integral_constant<int,

            // Where K = std::remove_reference_t<Obj>, CALLABLE_TRAITS_MAKE_CONSTEXPR(U&&)
            // resolves to a matching reference to a constexpr K object. Hence, K must be
            // a literal type with a constexpr default constructor. any_arg_evaluated<I>
            // is a "chameleon" type that tries to pass as anything. Generally, if K is
            // templated and uses dependent names, this will fail. However, There are a few
            // exceptions: Unary/binary operators, value member `value`, and member alias
            // `type` are all defined in terms of any_arg_evaluated<I>, so usage of these
            // will succeed in K.


                    ((CALLABLE_TRAITS_MAKE_CONSTEXPR(Obj).*std::remove_reference<P>::type::value)(
                        CALLABLE_TRAITS_MAKE_CONSTEXPR(Rgs&&)...
                    ), 0)>>;

            auto operator()(...) const -> substitution_failure;
        };

        template<typename OriginalType, typename Pmd, typename... Args>
        struct test_invoke_constexpr<pmd<OriginalType, Pmd>, Args...> {
            auto operator()(...) const -> substitution_failure;
        };

        template<typename F, typename... Args>
        struct test_invoke_constexpr<F, Args...> {

            //see comments on specialization above
            template<typename T, typename... Rgs>
            auto operator()(T&& t, Rgs&&...) const -> if_not_integral_constant<T,
                std::integral_constant<int,
                    (CALLABLE_TRAITS_MAKE_CONSTEXPR(T&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(Rgs&&)...), 0)>>;

            template<typename T, typename... Rgs, typename U = typename std::remove_reference<T>::type>
            auto operator()(T&& t, Rgs&&...) const -> if_integral_constant<T,
                std::integral_constant<int, (U::value(CALLABLE_TRAITS_MAKE_CONSTEXPR(Rgs&&)...), 0)>>;

            auto operator()(...) const -> substitution_failure;
        };

        template<typename... Ts>
        using are_all_constexpr_constructible = conjunction<
            is_constexpr_constructible<Ts>...
        >;

        template<typename T, typename... Args, typename std::enable_if<
            negate<are_all_constexpr_constructible<T, Args...>>::value, int>::type = 0>
        inline constexpr auto
        can_invoke_constexpr_impl(T&&, Args&&...) {
            return std::false_type{};
        }

        template<typename T, typename... Args, typename std::enable_if<
            are_all_constexpr_constructible<T, Args...>::value, int>::type = 0>
        inline constexpr auto
        can_invoke_constexpr_impl(T&& t, Args&&... args) {
            using traits = traits<T&&>;
            using test = test_invoke_constexpr<traits, Args&&...>;
            using result = decltype(test{}(::std::forward<T>(t), ::std::forward<Args>(args)...));
            using failure = substitution_failure;
            using is_invalid_invoke = std::is_same<result, failure>;
            return std::integral_constant<bool, !is_invalid_invoke::value>{};
        }

#endif //ifndef CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED
    }
}
#endif // CALLABLE_TRAITS_DETAIL_CAN_INVOKE_CONSTEXPR_T_HPP

