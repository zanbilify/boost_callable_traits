/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HPP
#define CALLABLE_TRAITS_HPP


#include <callable_traits/traits.hpp>
#include <callable_traits/pmd.hpp>
#include <callable_traits/pmf.hpp>
#include <callable_traits/function.hpp>
#include <callable_traits/function_object.hpp>
#include <callable_traits/general.hpp>
#include <callable_traits/disjunction.hpp>
#include <callable_traits/remove_reference_if_ptr.hpp>
#include <callable_traits/default_dispatch.hpp>
#include <callable_traits/can_invoke_t.hpp>
#include <callable_traits/substitution.hpp>
#include <callable_traits/arity.hpp>
#include <callable_traits/bind_args_t.hpp>

//todo remove?
#include <callable_traits/can_invoke_t.hpp>

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

        using invoke_t = callable_traits::ctdetail::test_invoke<
            ctdetail::traits<Callable&&>, Ts&&...
        >;

        return std::integral_constant<
            bool,
            !std::is_same<failure, decltype(invoke_t{}(
                std::forward<Callable>(c),
                std::forward<Ts>(ts)...
            ))>::value
        >{}; 
    }

    template<typename Callable>
    inline constexpr auto
    has_varargs(Callable&&) { 
        return typename ctdetail::traits<Callable&&>::has_varargs{};
    }

    template<typename Callable>
    inline constexpr auto
    has_varargs() {
        return typename ctdetail::traits<Callable>::has_varargs{};
    }

    template<std::size_t SearchLimit = constants::arity_search_limit, typename Callable>
    inline constexpr auto
    min_arity(Callable&&) {
        return ctdetail::min_arity_t<ctdetail::traits<Callable&&>, SearchLimit>{};
    }

    template<typename Callable, std::size_t SearchLimit = constants::arity_search_limit>
    inline constexpr auto
    min_arity() {
        return ctdetail::min_arity_t<ctdetail::traits<Callable>, SearchLimit>{};
    }

    template<std::size_t SearchLimit = constants::arity_search_limit, typename Callable>
    inline constexpr auto
    max_arity(Callable&&) {
        return ctdetail::max_arity_t<ctdetail::traits<Callable&&>, SearchLimit>{};
    }

    template<typename Callable, std::size_t SearchLimit = constants::arity_search_limit>
    inline constexpr auto
    max_arity() {
        return ctdetail::max_arity_t<ctdetail::traits<Callable>, SearchLimit>{};
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

    template<typename Callable, typename... Args>
    auto bind_args(Callable, Args...) ->
        typename ctdetail::bind_args_t<Callable, Args...>::type;
}

#endif