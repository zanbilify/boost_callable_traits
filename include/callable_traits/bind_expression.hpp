/*!
Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
Copyright (c) 2001 David Abrahams
Copyright (c) 2005 Peter Dimov
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_BIND_EXPRESSION_HPP
#define CALLABLE_TRAITS_BIND_EXPRESSION_HPP

#include <callable_traits/traits.hpp>
#include <callable_traits/categorize_bind_arg.hpp>
#include <callable_traits/tags.hpp>
#include <callable_traits/ph.hpp>
#include <callable_traits/sort_tuple.hpp>
#include <callable_traits/placeholder_routes.hpp>
#include <callable_traits/remove_duplicate_placeholders.hpp>
#include <callable_traits/fwd/bind_expression_fwd.hpp>
#include <callable_traits/prepend.hpp>
//#include <callable_traits/private_tuple.hpp>

#include <tuple>
#include <functional>

namespace callable_traits {
    
    namespace ctdetail {

        template<typename PhRouteLeft, typename PhRouteRight>
        struct compare_ph_value {
            static constexpr bool value = 
                PhRouteLeft::ph_value < PhRouteRight::ph_value;
        };

        template <typename PhRoutesTuple, typename OriginalArgsTuple, typename Seq>
        struct placeholders_mapped_to_original_signature;

        template <typename PhRoutesTuple, typename OriginalArgsTuple,  std::size_t... I>
        struct placeholders_mapped_to_original_signature<
            PhRoutesTuple, OriginalArgsTuple, std::index_sequence<I...>> {

            //this is where the magic happens
            using type = std::tuple<
                typename std::tuple_element<
                    std::tuple_element<I, PhRoutesTuple>::type::original_arg_index,
                    OriginalArgsTuple
                >::type...
            >;
        };

        template <typename PhRoutesTuple, std::size_t... I>
        struct placeholders_mapped_to_original_signature<
            PhRoutesTuple, std::tuple<>, std::index_sequence<I...>> {
            using type = std::tuple<>;
        };

        template <typename T, std::size_t... I>
        struct placeholders_mapped_to_original_signature<
            T, std::tuple<ambiguous_type>, std::index_sequence<I...>> {
            using type = std::tuple<ambiguous_type>;
        };

        template <typename...> struct bind_expressions_filter;

        template <> struct bind_expressions_filter<> { using type = std::tuple<>; };

        template <typename Head, typename... Tail>
        struct bind_expressions_filter<Head, Tail...> {
            using type = typename bind_expressions_filter<Tail...>::type;
        };

        template<typename Callable, typename... BindExprArgs, typename ...Tail>
        struct bind_expressions_filter<
            bind_expression<Callable, BindExprArgs...>, Tail...
        > {
            using type = typename prepend<
                bind_expression<Callable, BindExprArgs...>,
                typename bind_expressions_filter<Tail...>::type
            >::type;
        };

        template <typename... Ts>
        struct remove_non_bind_expressions {
            using type = typename bind_expressions_filter<Ts...>::type;
        };

        template<typename T>
        struct is_empty_tuple {
            using value_type = std::false_type;
        };

        template<>
        struct is_empty_tuple<std::tuple<>> {
            using value_type = std::true_type;
        };

        template<typename T>
        struct is_not_empty_tuple {
            using value_type = std::true_type;
        };

        template<>
        struct is_not_empty_tuple<std::tuple<>> {
            using value_type = std::false_type;
        };

        template <typename BindExpr, typename = std::true_type>
        struct flatten_bind_expressions;

        template <typename... BindExprs>
        struct flatten_bind_expressions<
            std::tuple<BindExprs...>,
            std::true_type
        > {
            using type = decltype(std::tuple_cat(
                std::declval<typename flatten_bind_expressions<BindExprs>::type>()...
            ));
        };

        template <typename BindExpr>
        struct flatten_bind_expressions<
            BindExpr,
            typename is_not_empty_tuple<typename BindExpr::inner_bind_expressions>::value_type
        > {
            using type = typename prepend<
                BindExpr,
                typename flatten_bind_expressions<
                    typename BindExpr::inner_bind_expressions
                >::type
            >::type;
        };

        //base case - bind expression has no inner bind expressions
        template <typename BindExpr>
        struct flatten_bind_expressions<
            BindExpr,
            typename is_empty_tuple<typename BindExpr::inner_bind_expressions>::value_type
        > {
            using type = std::tuple<BindExpr>;
        };

        template<typename Callable, typename... Args>
        struct bind_expression {

            using bind_args_tuple = std::tuple<
                typename categorize_bind_arg<Args>::type...
            >;

            using inner_bind_expressions =
                typename remove_non_bind_expressions<Args...>::type;

            using has_inner_bind_expressions = std::is_same<
                inner_bind_expressions, std::tuple<>
            >;

            using flattened_bind_expressions =
                typename flatten_bind_expressions<bind_expression>::type;

            using placeholder_route_map = typename placeholder_routes<
                bind_expression,
                bind_args_tuple
            >::type;

            using sorted_placeholder_routes =
                typename remove_duplicate_placeholders<
                    sort_tuple<
                        placeholder_route_map,
                        compare_ph_value
                    >
                >::type;

            using placeholder_count = std::tuple_size<
                sorted_placeholder_routes
            >;

            using original_args = typename traits<Callable>::arg_types;

            /*using arg_types = typename placeholders_mapped_to_original_signature<
                sorted_placeholder_routes,
                original_args,
                std::make_index_sequence<placeholder_count::value>
            >::type;*/

            using return_type = typename traits<Callable>::return_type;
        };

    }
}

#endif