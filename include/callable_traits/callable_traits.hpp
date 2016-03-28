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

    namespace no_sfinae {

        template<typename T>
        using args = typename ctdetail::traits<T>::arg_types;

        template<typename T>
        using signature = typename ctdetail::traits<T>::function_type;

        template<typename T>
        using qualified_signature = typename ctdetail::traits<T>::abominable_type;

        template<typename T>
        using result_of = typename ctdetail::traits<T>::return_type;

        template<typename T>
        using remove_const_qualifier =
            typename ctdetail::traits<T>::remove_const;

        template<typename T>
        using remove_volatile_qualifier =
            typename ctdetail::traits<T>::remove_volatile;

        template<typename T>
        using remove_cv_qualifiers =
            typename ctdetail::traits<T>::remove_cv;

        template<typename T>
        using remove_reference_qualifier =
            typename ctdetail::traits<T>::remove_reference;

        template<typename T>
        using remove_varargs =
            typename ctdetail::traits<T>::remove_varargs;

        template<typename T>
        using add_const_qualifier =
            typename ctdetail::traits<T>::add_const;

        template<typename T>
        using add_volatile_qualifier =
            typename ctdetail::traits<T>::add_volatile;

        template<typename T>
        using add_cv_qualifiers =
            typename ctdetail::traits<T>::add_cv;

        template<typename T>
        using add_lvalue_qualifier =
            typename ctdetail::traits<T>::add_lvalue_reference;

        template<typename T>
        using add_rvalue_qualifier =
            typename ctdetail::traits<T>::add_rvalue_reference;

        template<typename T>
        using add_varargs =
            typename ctdetail::traits<T>::add_varargs;
    }

    namespace ctdetail {

        template<typename T>
        using if_valid = typename std::enable_if<
            !std::is_same<T, unknown>::value
                && !std::is_same<T, invalid_type>::value,
            T
        >::type;
    }

    template<typename T>
    using args = ctdetail::if_valid<no_sfinae::args<T>>;

    template<size_t I, typename T>
    using arg_at = ctdetail::if_valid<typename std::tuple_element<I, no_sfinae::args<T>>::type>;

    template<typename T>
    using signature = ctdetail::if_valid<no_sfinae::signature<T>>;

    template<typename T>
    using qualified_signature = ctdetail::if_valid<no_sfinae::qualified_signature<T>>;

    template<typename T>
    using result_of = ctdetail::if_valid<no_sfinae::result_of<T>>;

    template<typename T>
    using remove_const_qualifier = ctdetail::if_valid<no_sfinae::remove_const_qualifier<T>>;

    template<typename T>
    using remove_volatile_qualifier = ctdetail::if_valid<no_sfinae::remove_volatile_qualifier<T>>;

    template<typename T>
    using remove_cv_qualifiers = ctdetail::if_valid<no_sfinae::remove_cv_qualifiers<T>>;

    template<typename T>
    using remove_reference_qualifier = ctdetail::if_valid<no_sfinae::remove_reference_qualifier<T>>;

    template<typename T>
    using add_const_qualifier = ctdetail::if_valid<no_sfinae::add_const_qualifier<T>>;

    template<typename T>
    using add_volatile_qualifier = ctdetail::if_valid<no_sfinae::add_volatile_qualifier<T>>;

    template<typename T>
    using add_cv_qualifiers = ctdetail::if_valid<no_sfinae::add_cv_qualifiers<T>>;

    template<typename T>
    using add_lvalue_qualifier = ctdetail::if_valid<no_sfinae::add_lvalue_qualifier<T>>;

    template<typename T>
    using add_rvalue_qualifier = ctdetail::if_valid<no_sfinae::add_rvalue_qualifier<T>>;

    template<typename T>
    using add_varargs = ctdetail::if_valid<no_sfinae::add_varargs<T>>;

    template<typename T>
    using remove_varargs = ctdetail::if_valid<no_sfinae::remove_varargs<T>>;

    template<typename T, typename... Args>
    inline constexpr auto
    can_invoke(T&& t, Args&&... args) {
        using traits = ctdetail::traits<T&&>;
        using test = ctdetail::test_invoke<traits, Args&&...>;
        using result = decltype(test{}(::std::forward<T>(t), ::std::forward<Args>(args)...));
        using failure = ctdetail::substitution_failure;
        using is_invalid_invoke = std::is_same<result, failure>;
        return std::integral_constant<bool, !is_invalid_invoke::value>{};
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

    template<typename T>
    inline constexpr auto
    has_varargs(T&&) {
        return typename ctdetail::traits<T&&>::has_varargs{};
    }

    template<typename T>
    inline constexpr auto
    has_varargs() {
        return typename ctdetail::traits<T>::has_varargs{};
    }

    template< std::size_t SearchLimit = constants::arity_search_limit, typename T>
    inline constexpr auto
    min_arity(T&&) {
        using traits = ctdetail::traits<T&&>;
        return ctdetail::min_arity_t<traits, SearchLimit>{};
    }

    template<typename T, std::size_t SearchLimit = constants::arity_search_limit>
    inline constexpr auto
    min_arity() {
        using traits = ctdetail::traits<T>;
        return ctdetail::min_arity_t<traits, SearchLimit>{};
    }

    template<std::size_t SearchLimit = constants::arity_search_limit, typename T>
    inline constexpr auto
    max_arity(T&&) {
        return ctdetail::max_arity_t<ctdetail::traits<T&&>, SearchLimit>{};
    }

    template<typename T, std::size_t SearchLimit = constants::arity_search_limit>
    inline constexpr auto
    max_arity() {
        return ctdetail::max_arity_t<ctdetail::traits<T>, SearchLimit>{};
    }

    template<typename T>
    inline constexpr auto
    arity(T&&) {
        return ctdetail::arity_t<ctdetail::traits<T&&>>{};
    }

    template<typename T>
    inline constexpr auto
    arity() {
        return ctdetail::arity_t<ctdetail::traits<T>>{};
    }

    template<typename T, typename... Args>
    inline constexpr auto
    bind_expr(T, Args...) -> ctdetail::bind_expression<T, Args...> {
        return{};
    }

    template<typename T>
    inline constexpr auto
    is_unqualified() {
        return typename ctdetail::traits<T>::is_unqualified{};
    }

    template<typename T>
    inline constexpr auto
    is_unqualified(T&&) {
        return typename ctdetail::traits<T&&>::is_unqualified{};
    }

    template<typename T>
    inline constexpr auto
    is_const_qualified() {
        return typename ctdetail::traits<T>::is_const_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_const_qualified(T&&) {
        return typename ctdetail::traits<T&&>::is_const_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_cv_qualified() {
        return typename ctdetail::traits<T>::is_cv_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_cv_qualified(T&&) {
        return typename ctdetail::traits<T&&>::is_cv_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_volatile_qualified() {
        return typename ctdetail::traits<T>::is_volatile_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_volatile_qualified(T&&) {
        return typename ctdetail::traits<T&&>::is_volatile_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_reference_qualified() {
        return typename ctdetail::traits<T>::is_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_reference_qualified(T&&) {
        return typename ctdetail::traits<T&&>::is_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_lvalue_reference_qualified() {
        return typename ctdetail::traits<T>::is_lvalue_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_lvalue_reference_qualified(T&&) {
        return typename ctdetail::traits<T&&>::is_lvalue_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_rvalue_reference_qualified() {
        return typename ctdetail::traits<T>::is_rvalue_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_rvalue_reference_qualified(T&&) {
        return typename ctdetail::traits<T&&>::is_rvalue_reference_qualified{};
    }
}

#ifdef _MSVC_VER
#pragma warning(pop)
#endif //ifdef _MSVC_VER

#endif
