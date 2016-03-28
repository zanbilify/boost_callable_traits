/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_INTERFACE_HPP
#define CALLABLE_TRAITS_INTERFACE_HPP

#include <callable_traits/traits.hpp>
#include <callable_traits/pmd.hpp>
#include <callable_traits/pmf.hpp>
#include <callable_traits/function.hpp>
#include <callable_traits/function_object.hpp>
#include <callable_traits/substitution.hpp>
#include <callable_traits/arity.hpp>
#include <callable_traits/bind_expression.hpp>
#include <callable_traits/bind_expression_parser.hpp>
#include <callable_traits/shallow_decay.hpp>
#include <callable_traits/disjunction.hpp>
#include <type_traits>
#include <utility>

namespace callable_traits {

    namespace no_sfinae {

        template<typename T>
        using args = typename detail::traits<T>::arg_types;

        template<size_t I, typename T>
        using arg_at = typename detail::disjunction<
            detail::value_type_pair<std::tuple_size<args<T>>::value <= I, invalid_type>,
            detail::value_type_pair<true, typename std::tuple_element<I, no_sfinae::args<T>>::type>
        >::type;

        template<typename T>
        using signature = typename detail::traits<T>::function_type;

        template<typename T>
        using qualified_signature = typename detail::traits<T>::abominable_type;

        template<typename T>
        using result_of = typename detail::traits<T>::return_type;

        template<typename T>
        using remove_const_qualifier =
            typename detail::traits<T>::remove_const;

        template<typename T>
        using remove_volatile_qualifier =
            typename detail::traits<T>::remove_volatile;

        template<typename T>
        using remove_cv_qualifiers =
            typename detail::traits<T>::remove_cv;

        template<typename T>
        using remove_reference_qualifier =
            typename detail::traits<T>::remove_reference;

        template<typename T>
        using remove_varargs =
            typename detail::traits<T>::remove_varargs;

        template<typename T>
        using add_const_qualifier =
            typename detail::traits<T>::add_const;

        template<typename T>
        using add_volatile_qualifier =
            typename detail::traits<T>::add_volatile;

        template<typename T>
        using add_cv_qualifiers =
            typename detail::traits<T>::add_cv;

        template<typename T>
        using add_lvalue_qualifier =
            typename detail::traits<T>::add_lvalue_reference;

        template<typename T>
        using add_rvalue_qualifier =
            typename detail::traits<T>::add_rvalue_reference;

        template<typename T>
        using add_varargs =
            typename detail::traits<T>::add_varargs;
    }

    namespace detail {

        template<typename T>
        using if_valid = typename std::enable_if<
            !std::is_same<T, unknown>::value
                && !std::is_same<T, invalid_type>::value,
            T
        >::type;
    }

    template<typename T>
    using args = detail::if_valid<no_sfinae::args<T>>;

    template<size_t I, typename T>
    using arg_at = detail::if_valid<typename std::tuple_element<I, no_sfinae::args<T>>::type>;

    template<typename T>
    using signature = detail::if_valid<no_sfinae::signature<T>>;

    template<typename T>
    using qualified_signature = detail::if_valid<no_sfinae::qualified_signature<T>>;

    template<typename T>
    using result_of = detail::if_valid<no_sfinae::result_of<T>>;

    template<typename T>
    using remove_const_qualifier = detail::if_valid<no_sfinae::remove_const_qualifier<T>>;

    template<typename T>
    using remove_volatile_qualifier = detail::if_valid<no_sfinae::remove_volatile_qualifier<T>>;

    template<typename T>
    using remove_cv_qualifiers = detail::if_valid<no_sfinae::remove_cv_qualifiers<T>>;

    template<typename T>
    using remove_reference_qualifier = detail::if_valid<no_sfinae::remove_reference_qualifier<T>>;

    template<typename T>
    using add_const_qualifier = detail::if_valid<no_sfinae::add_const_qualifier<T>>;

    template<typename T>
    using add_volatile_qualifier = detail::if_valid<no_sfinae::add_volatile_qualifier<T>>;

    template<typename T>
    using add_cv_qualifiers = detail::if_valid<no_sfinae::add_cv_qualifiers<T>>;

    template<typename T>
    using add_lvalue_qualifier = detail::if_valid<no_sfinae::add_lvalue_qualifier<T>>;

    template<typename T>
    using add_rvalue_qualifier = detail::if_valid<no_sfinae::add_rvalue_qualifier<T>>;

    template<typename T>
    using add_varargs = detail::if_valid<no_sfinae::add_varargs<T>>;

    template<typename T>
    using remove_varargs = detail::if_valid<no_sfinae::remove_varargs<T>>;

    template<typename T, typename... Args>
    inline constexpr auto
    can_invoke(T&& t, Args&&... args) {
        using traits = detail::traits<T&&>;
        using test = detail::test_invoke<traits, Args&&...>;
        using result = decltype(test{}(::std::forward<T>(t), ::std::forward<Args>(args)...));
        using failure = detail::substitution_failure;
        using is_invalid_invoke = std::is_same<result, failure>;
        return std::integral_constant<bool, !is_invalid_invoke::value>{};
    }

    template<typename T>
    inline constexpr auto
    is_overloaded(T&&) {
        return typename detail::traits<T&&>::is_ambiguous{};
    }

    template<typename T>
    inline constexpr auto
    is_overloaded() {
        return typename detail::traits<T>::is_ambiguous{};
    }

    template<typename T>
    inline constexpr auto
    has_varargs(T&&) {
        return typename detail::traits<T&&>::has_varargs{};
    }

    template<typename T>
    inline constexpr auto
    has_varargs() {
        return typename detail::traits<T>::has_varargs{};
    }

    template< std::size_t SearchLimit = constants::arity_search_limit, typename T>
    inline constexpr auto
    min_arity(T&&) {
        using traits = detail::traits<T&&>;
        return detail::min_arity_t<traits, SearchLimit>{};
    }

    template<typename T, std::size_t SearchLimit = constants::arity_search_limit>
    inline constexpr auto
    min_arity() {
        using traits = detail::traits<T>;
        return detail::min_arity_t<traits, SearchLimit>{};
    }

    template<std::size_t SearchLimit = constants::arity_search_limit, typename T>
    inline constexpr auto
    max_arity(T&&) {
        return detail::max_arity_t<detail::traits<T&&>, SearchLimit>{};
    }

    template<typename T, std::size_t SearchLimit = constants::arity_search_limit>
    inline constexpr auto
    max_arity() {
        return detail::max_arity_t<detail::traits<T>, SearchLimit>{};
    }

    template<typename T>
    inline constexpr auto
    arity(T&&) {
        return detail::arity_t<detail::traits<T&&>>{};
    }

    template<typename T>
    inline constexpr auto
    arity() {
        return detail::arity_t<detail::traits<T>>{};
    }

    template<typename T, typename... Args>
    inline constexpr auto
    bind_expr(T, Args...) -> detail::bind_expression<T, Args...> {
        return{};
    }

    template<typename T>
    inline constexpr auto
    is_unqualified() {
        return typename detail::traits<T>::is_unqualified{};
    }

    template<typename T>
    inline constexpr auto
    is_unqualified(T&&) {
        return typename detail::traits<T&&>::is_unqualified{};
    }

    template<typename T>
    inline constexpr auto
    is_const_qualified() {
        return typename detail::traits<T>::is_const_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_const_qualified(T&&) {
        return typename detail::traits<T&&>::is_const_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_cv_qualified() {
        return typename detail::traits<T>::is_cv_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_cv_qualified(T&&) {
        return typename detail::traits<T&&>::is_cv_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_volatile_qualified() {
        return typename detail::traits<T>::is_volatile_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_volatile_qualified(T&&) {
        return typename detail::traits<T&&>::is_volatile_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_reference_qualified() {
        return typename detail::traits<T>::is_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_reference_qualified(T&&) {
        return typename detail::traits<T&&>::is_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_lvalue_reference_qualified() {
        return typename detail::traits<T>::is_lvalue_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_lvalue_reference_qualified(T&&) {
        return typename detail::traits<T&&>::is_lvalue_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_rvalue_reference_qualified() {
        return typename detail::traits<T>::is_rvalue_reference_qualified{};
    }

    template<typename T>
    inline constexpr auto
    is_rvalue_reference_qualified(T&&) {
        return typename detail::traits<T&&>::is_rvalue_reference_qualified{};
    }
}

#ifdef _MSVC_VER
#pragma warning(pop)
#endif //ifdef _MSVC_VER

#endif
