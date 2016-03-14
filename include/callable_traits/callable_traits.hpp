/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HPP
#define CALLABLE_TRAITS_HPP


#include <callable/traits_dispatch.hpp>
#include <callable/can_invoke_t.hpp>
#include <callable/substitution.hpp>
#include <callable/arity.hpp>

#include <type_traits>

namespace callable_traits {

    template<typename T, typename U = typename std::remove_reference<T>::type>
    inline constexpr
    std::integral_constant<bool, ctdetail::traits<U>::is_ambiguous>
    is_ambiguous(T&&) {
        return{};
    }

    template<typename T>
    using args = typename ctdetail::traits<T>::arg_types;

    template<size_t Index, typename T>
    using arg_at = typename std::tuple_element<Index, args<T>>::type;

    template<typename T>
    using result_of = typename ctdetail::traits<T>::return_type;

    template<typename Callable, typename... Ts>
    inline constexpr auto
    can_invoke(Callable&& c, Ts&&... ts) {
        using failure = callable_traits::ctdetail::substitution_failure;
        using invoke_t = callable_traits::ctdetail::test_invoke<ctdetail::traits<Callable&&>, Ts&&...>;

        return std::integral_constant<
            bool,
            !std::is_same<failure, decltype(invoke_t{}(
                static_cast<Callable&&>(c),
                std::forward<Ts>(ts)...
            ))>::value
        >{}; 
    }

    template<typename Callable>
    inline constexpr auto
    has_varargs(Callable&& c) { 
        return typename ctdetail::traits<Callable&&>::has_varargs{};
    }

    template<typename Callable>
    inline constexpr auto
    has_varargs() {
        return typename ctdetail::traits<Callable>::has_varargs{};
    }

    template<typename Callable>
    inline constexpr auto
    min_arity(Callable&&) {
        return ctdetail::min_arity_t<ctdetail::traits<Callable&&>>{};
    }

    template<typename Callable>
    inline constexpr auto
    min_arity() {
        return ctdetail::min_arity_t<ctdetail::traits<Callable>>{};
    }

    template<typename Callable>
    inline constexpr auto
    max_arity(Callable&&) {
        return ctdetail::max_arity_t<ctdetail::traits<Callable&&>>{};
    }

    template<typename Callable>
    inline constexpr auto
    max_arity() {
        return ctdetail::max_arity_t<ctdetail::traits<Callable>>{};
    }

    template<typename Callable>
    inline constexpr auto
    arity(Callable&&) {
        return ctdetail::arity_t<ctdetail::traits<Callable&&>>{};
    }

    template<typename Callable>
    inline constexpr auto
    arity() {
        return ctdetail::arity_t<ctdetail::traits<Callable>>{};
    }
}

#endif