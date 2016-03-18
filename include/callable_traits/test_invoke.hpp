 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DECLVOKE_HPP
#define CALLABLE_TRAITS_DECLVOKE_HPP

#include <callable_traits/substitution.hpp>
#include <callable_traits/normalize_reference.hpp>

#include <type_traits>
#include <utility>

namespace callable_traits {

    namespace ctdetail {
        
        template<typename...>
        struct test_invoke;

        template<typename Pmf, typename T, typename... Args>
        struct test_invoke<pmf<Pmf>, T, Args...> {

            using dispatch = pmf<Pmf>;
            using base = typename dispatch::class_type;
            using derived = typename std::remove_cv<
                typename std::remove_reference<T>::type
            >::type;

            static constexpr bool is_value_invocation = 
                std::is_base_of<base, derived>::value
                || std::is_same<base, derived>::value;

            template<typename P, typename U, typename... Rgs,
                CALLABLE_TRAITS_REQUIRES_(is_value_invocation)>
            auto operator()(P&& p, U&& u, Rgs&&... rgs) const ->
            substitution_success<decltype(
                (std::forward<U>(u).*p)(std::forward<Rgs>(rgs)...)
            )>;

           template<typename P, typename U, typename... Rgs,
                CALLABLE_TRAITS_REQUIRES_(!is_value_invocation)>
            auto operator()(P&& p, U&& u, Rgs&&... rgs) const ->
            substitution_success<decltype(
                (std::declval<normalize_reference<U&&>>().*p)
                    (std::forward<Rgs>(rgs)...)
            )>;

            substitution_failure operator()(...) const;

            static constexpr int arg_count = sizeof...(Args) - 1;
        };

        template<typename Pmd, typename T>
        struct test_invoke<pmd<Pmd>, T> {

            using dispatch = pmd<Pmd>;
            using base = typename dispatch::class_type;
            using derived = typename std::remove_cv<
                typename std::remove_reference<T>::type
            >::type;

            static constexpr bool is_value_invocation =
                std::is_base_of<base, derived>::value
                || std::is_same<base, derived>::value;

            template<
                typename P,
                typename U,
                CALLABLE_TRAITS_REQUIRES_(is_value_invocation)
            >
            auto operator()(P&&, U&&) const ->
            substitution_success<decltype(
                (std::declval<U&&>().*std::declval<P&&>())
            )>;

            template<
                typename P,
                typename U,
                CALLABLE_TRAITS_REQUIRES_(!is_value_invocation)
            >
            auto operator()(P&& p, U&& u) const ->
            substitution_success<decltype(
                (std::declval<normalize_reference<U&&>>().*p)
            )>;

            substitution_failure operator()(...) const;

            static constexpr int arg_count = -1;
        };

        template<typename F, typename... Args>
        struct test_invoke<F, Args...> {

            template<typename T, typename... Rgs>
            auto operator()(T&& t, Rgs&&... rgs) const ->
            substitution_success<
                decltype(static_cast<T&&>(t)(std::forward<Rgs>(rgs)...))
            >;

            substitution_failure operator()(...) const;

            static constexpr int arg_count = sizeof...(Args);
        };
    }
}

#endif