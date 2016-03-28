/*!
Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
Copyright (c) 2001 David Abrahams
Copyright (c) 2005 Peter Dimov
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS__DETAIL_BIND_EXPRESSION_HPP
#define CALLABLE_TRAITS__DETAIL_BIND_EXPRESSION_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/categorize_bind_arg.hpp>
#include <callable_traits/detail/placeholder.hpp>
#include <callable_traits/detail/fwd/bind_expression_fwd.hpp>
#include <callable_traits/detail/prepend.hpp>
//#include <callable_traits/detail/private_tuple.hpp>

#include <tuple>
#include <functional>

namespace callable_traits {
    
    namespace detail {

        template<typename PhRouteLeft, typename PhRouteRight>
        struct compare_ph_value {
            static constexpr bool value = 
                PhRouteLeft::ph_value < PhRouteRight::ph_value;
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

            using flattened_bind_expressions =
                typename flatten_bind_expressions<bind_expression>::type;

            using placeholder_route_map = typename placeholder_routes<
                bind_expression,
                bind_args_tuple
            >::type;

            using original_args = typename traits<Callable>::arg_types;
            using return_type = typename traits<Callable>::return_type;
        };

    }
}

#endif