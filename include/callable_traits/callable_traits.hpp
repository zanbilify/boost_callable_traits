/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HPP
#define CALLABLE_TRAITS_HPP

#ifdef _MSVC_VER
#pragma warning(push)
// disabling the MSVC warning about symbol truncation. This is
// harmless, because none of these symbols are involved in linking.
#pragma warning(disable : 4503)
#endif //ifdef _MSVC_VER

#include <callable_traits/traits.hpp>
#include <callable_traits/pmd.hpp>
#include <callable_traits/pmf.hpp>
#include <callable_traits/function.hpp>
#include <callable_traits/function_object.hpp>
#include <callable_traits/general.hpp>
#include <callable_traits/remove_reference_if_ptr.hpp>
#include <callable_traits/default_dispatch.hpp>
#include <callable_traits/can_invoke_t.hpp>
#include <callable_traits/substitution.hpp>
#include <callable_traits/arity.hpp>
#include <callable_traits/bind_expression.hpp>
#include <callable_traits/bind_expression_parser.hpp>
#include <callable_traits/is_bind_expression.hpp>
#include <callable_traits/shallow_decay.hpp>

//todo remove?
#include <callable_traits/can_invoke_t.hpp>

#include <type_traits>
#include <utility>

namespace callable_traits {

    template<typename T, typename U = ctdetail::shallow_decay<T>>
    using args = typename ctdetail::traits<T>::arg_types;

    template<typename T, typename U = ctdetail::shallow_decay<T>>
    using signature = typename ctdetail::traits<T>::function_type;

    template<typename T, typename U = ctdetail::shallow_decay<T>>
    using qualified_signature = typename ctdetail::traits<T>::abominable_type;

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

    template<typename T>
    inline constexpr auto
    is_overloaded(T&&) {
        return typename ctdetail::traits<T&&>::is_ambiguous{};
    }

    template<typename T>
    inline constexpr auto
    is_overloaded() {
        return typename ctdetail::traits<T>::is_ambiguous{};
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
    inline constexpr auto
    bind_expr(Callable, Args...) ->
        ctdetail::bind_expression<Callable, Args...> {
        return{};
    }

    template<typename Callable>
    inline constexpr auto
    is_unqualified() {
        return typename ctdetail::traits<Callable>::is_const_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_unqualified(Callable&&) {
        return typename ctdetail::traits<Callable&&>::is_const_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_const_qualified() {
        return typename ctdetail::traits<Callable>::is_const_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_const_qualified(Callable&&) {
        return typename ctdetail::traits<Callable&&>::is_const_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_cv_qualified() {
        return typename ctdetail::traits<Callable>::is_cv_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_cv_qualified(Callable&&) {
        return typename ctdetail::traits<Callable&&>::is_cv_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_volatile_qualified() {
        return typename ctdetail::traits<Callable>::is_volatile_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_volatile_qualified(Callable&&) {
        return typename ctdetail::traits<Callable&&>::is_volatile_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_reference_qualified() {
        return typename ctdetail::traits<Callable>::is_reference_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_reference_qualified(Callable&&) {
        return typename ctdetail::traits<Callable&&>::is_reference_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_lvalue_reference_qualified() {
        return typename ctdetail::traits<Callable>::is_lvalue_reference_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_lvalue_reference_qualified(Callable&&) {
        return typename ctdetail::traits<Callable&&>::is_lvalue_reference_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_rvalue_reference_qualified() {
        return typename ctdetail::traits<Callable>::is_rvalue_reference_qualified{};
    }

    template<typename Callable>
    inline constexpr auto
    is_rvalue_reference_qualified(Callable&&) {
        return typename ctdetail::traits<Callable&&>::is_rvalue_reference_qualified{};
    }

    template<typename Callable>
    using remove_const_qualifier =
        typename ctdetail::traits<Callable>::remove_const;

    template<typename Callable>
    using remove_volatile_qualifier =
        typename ctdetail::traits<Callable>::remove_volatile;

    template<typename Callable>
    using remove_cv_qualifiers =
        typename ctdetail::traits<Callable>::remove_cv;

    template<typename Callable>
    using remove_reference_qualifier =
        typename ctdetail::traits<Callable>::remove_reference;

    template<typename Callable>
    using remove_varargs =
        typename ctdetail::traits<Callable>::remove_varargs;

    template<typename Callable>
    using add_const_qualifier =
        typename ctdetail::traits<Callable>::add_const;

    template<typename Callable>
    using add_volatile_qualifier =
        typename ctdetail::traits<Callable>::add_volatile;

    template<typename Callable>
    using add_cv_qualifiers =
        typename ctdetail::traits<Callable>::add_cv;

    template<typename Callable>
    using add_lvalue_qualifier =
        typename ctdetail::traits<Callable>::add_lvalue_reference;

    template<typename Callable>
    using add_rvalue_qualifier =
        typename ctdetail::traits<Callable>::add_rvalue_reference;

    template<typename Callable>
    using add_varargs =
        typename ctdetail::traits<Callable>::add_varargs;
}

#ifdef _MSVC_VER
#pragma warning(pop)
#endif //ifdef _MSVC_VER

#endif
