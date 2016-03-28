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
#include <callable_traits/shallow_decay.hpp>

#include <type_traits>
#include <utility>

namespace callable_traits {

    namespace ctdetail {
        
        template<typename T>
        struct subst_success {};

        template<typename Base, typename T,
                 typename IsBaseOf = std::is_base_of<Base, shallow_decay<T>>,
                 typename IsSame = std::is_same<Base, shallow_decay<T>>>
        using generalize_if_dissimilar = typename std::conditional<
            IsBaseOf::value || IsSame::value, T, normalize_ptr_or_reference<T>
        >::type;

        template<typename...>
        struct test_invoke;

        template<typename Pmf, typename T, typename... Args>
        struct test_invoke<pmf<Pmf>, T, Args...> {

            using class_t = typename pmf<Pmf>::class_type;

           template<typename P, typename U, typename... Rgs,
                typename Obj = generalize_if_dissimilar<class_t, U&&>>
            auto operator()(P&& p, U&& u, Rgs&&... rgs) const ->
                subst_success<decltype((std::declval<Obj>().*p)(std::forward<Rgs>(rgs)...))>;

            auto operator()(...) const -> substitution_failure;

            static constexpr int arg_count = sizeof...(Args) - 1;
        };

        template<typename Pmd, typename... Args>
        struct test_invoke<pmd<Pmd>, Args...> {

            using class_t = typename pmd<Pmd>::class_type;

            template<typename P, typename U,
                typename Obj = generalize_if_dissimilar<class_t, U&&>>
            auto operator()(P&& p, U&& u) const ->
                subst_success<decltype((std::declval<Obj>().*p))>;

            auto operator()(...) const -> substitution_failure;

            static constexpr int arg_count = -1;
        };

        template<typename F, typename... Args>
        struct test_invoke<F, Args...> {

            template<typename T, typename... Rgs,
                typename U = normalize_reference<T&&>>
            auto operator()(T&& t, Rgs&&... rgs) const ->
                subst_success<decltype(std::declval<U>()(std::forward<Rgs>(rgs)...))>;

            auto operator()(...) const -> substitution_failure;

            static constexpr int arg_count = sizeof...(Args);
        };
    }
}

#endif
