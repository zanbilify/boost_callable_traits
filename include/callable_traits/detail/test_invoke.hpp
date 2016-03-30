 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_TEST_INVOKE_HPP
#define CALLABLE_TRAITS_DETAIL_TEST_INVOKE_HPP

#include <callable_traits/detail/substitution.hpp>
#include <callable_traits/detail/generalize.hpp>
#include <callable_traits/detail/unwrap_reference.hpp>
#include <callable_traits/detail/is_integral_constant.hpp>
#include <callable_traits/detail/shallow_decay.hpp>
#include <callable_traits/detail/make_constexpr.hpp>
#include <callable_traits/config.hpp>

#include <type_traits>
#include <utility>

namespace callable_traits {

    namespace detail {
        
        template<typename T>
        struct success {};

        template<typename Base, typename T,
                 typename IsBaseOf = std::is_base_of<Base, shallow_decay<T>>,
                 typename IsSame = std::is_same<Base, shallow_decay<T>>>
        using generalize_if_dissimilar = typename std::conditional<
            IsBaseOf::value || IsSame::value, T, generalize<T>
        >::type;

        template<typename...>
        struct test_invoke;

        template<typename Pmf, typename T, typename... Args>
        struct test_invoke<pmf<Pmf>, T, Args...> {

            using class_t = typename pmf<Pmf>::class_type;

           template<typename P, typename U, typename... Rgs,
                typename Obj = generalize_if_dissimilar<class_t, U&&>>
            auto operator()(P&& p, U&& u, Rgs&&... rgs) const ->
                success<decltype((std::declval<Obj>().*p)(std::forward<Rgs>(rgs)...))>;

            auto operator()(...) const -> substitution_failure;

            static constexpr int arg_count = sizeof...(Args) - 1;
        };

        template<typename Pmd, typename... Args>
        struct test_invoke<pmd<Pmd>, Args...> {

            using class_t = typename pmd<Pmd>::class_type;

            template<typename P, typename U,
                typename Obj = generalize_if_dissimilar<class_t, U&&>>
            auto operator()(P&& p, U&& u) const ->
                success<decltype((std::declval<Obj>().*p))>;

            auto operator()(...) const -> substitution_failure;

            static constexpr int arg_count = 0;
        };

        template<typename F, typename... Args>
        struct test_invoke<F, Args...> {

            template<typename T, typename... Rgs,
                typename U = unwrap_reference<T&&>>
            auto operator()(T&& t, Rgs&&... rgs) const ->
                success<decltype(std::declval<U>()(std::forward<Rgs>(rgs)...))>;

            auto operator()(...) const -> substitution_failure;

            static constexpr int arg_count = sizeof...(Args);
        };

        template<typename...>
        struct test_invoke_constexpr {
            auto operator()(...) const->substitution_failure;
        };

#ifndef CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED

        template<typename Pmf, typename T, typename... Args>
        struct test_invoke_constexpr<pmf<Pmf>, T, Args...> {

            using class_t = typename pmf<Pmf>::class_type;

            template<typename P, typename U, typename... Rgs,
                typename Obj = generalize_if_dissimilar<class_t, U&&>>
            auto operator()(P&& p, U&& u, Rgs&&... rgs) const -> if_integral_constant<P,
                std::integral_constant<int,
                    ((CALLABLE_TRAITS_MAKE_CONSTEXPR(Obj).*std::remove_reference<P>::type::value)(
                        CALLABLE_TRAITS_MAKE_CONSTEXPR(Rgs&&)...
                    ), 0)>>;

            auto operator()(...) const -> substitution_failure;
        };

        template<typename Pmd, typename... Args>
        struct test_invoke_constexpr<pmd<Pmd>, Args...> {
            auto operator()(...) const -> substitution_failure;
        };

        template<typename F, typename... Args>
        struct test_invoke_constexpr<F, Args...> {

            template<typename T, typename... Rgs>
            auto operator()(T&& t, Rgs&&...) const -> if_not_integral_constant<T,
                std::integral_constant<int,
                    (CALLABLE_TRAITS_MAKE_CONSTEXPR(T&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(Rgs&&)...), 0)>>;

            template<typename T, typename... Rgs, typename U = typename std::remove_reference<T>::type>
            auto operator()(T&& t, Rgs&&...) const -> if_integral_constant<T,
                std::integral_constant<int, (U::value(CALLABLE_TRAITS_MAKE_CONSTEXPR(Rgs&&)...), 0)>>;

            auto operator()(...) const -> substitution_failure;
        };

#endif //ifndef CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED
    }
}

#endif
