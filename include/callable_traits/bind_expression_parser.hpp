/*!
Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
Copyright (c) 2001 David Abrahams
Copyright (c) 2005 Peter Dimov
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_BIND_EXPRESSION_PARSER_HPP
#define CALLABLE_TRAITS_BIND_EXPRESSION_PARSER_HPP

#include <callable_traits/traits.hpp>
#include <callable_traits/tuple_group_by.hpp>
#include <callable_traits/sort_tuple.hpp>
#include <callable_traits/bind_expression.hpp>
#include <tuple>
#include <functional>

namespace callable_traits {
    
    namespace ctdetail {

        template<typename BindExpressionTuple>
        struct combined_placeholder_routes;

        template<typename... BindExprs>
        struct combined_placeholder_routes<std::tuple<BindExprs...>> {

            using placeholder_route_map = decltype(std::tuple_cat(std::declval<
                typename placeholder_routes<
                    BindExprs,
                    typename BindExprs::bind_args_tuple
            >::type>()...));

            using type = sort_tuple<
                placeholder_route_map,
                compare_ph_value
            >;
        };

        template<typename T>
        struct ph_value_wrapper {
            static constexpr const auto value = T::ph_value;
        };

        template <typename...> struct filter_invalid_args;

        template <> struct filter_invalid_args<> {
            using type = std::tuple<>;
        };

        template <typename Head, typename ...Tail>
        struct filter_invalid_args<Head, Tail...> {

            static constexpr const auto is_legal_arg =
                !std::is_same<Head, any_arg<>>{}
                && !std::is_same<Head, ambiguous_type>{}
                && !std::is_same<Head, invalid_type>{};

            using type = typename std::conditional<
                is_legal_arg,
                typename prepend<Head, typename filter_invalid_args<Tail...>::type>::type,
                typename filter_invalid_args<Tail...>::type
            >::type;
        };

        template<typename Tup>
        struct valid_args;

        template<typename... Ts>
        struct valid_args<std::tuple<Ts...>> {
            using filtered_args = typename filter_invalid_args<Ts...>::type;
            using type = typename std::conditional<
                std::is_same<filtered_args, std::tuple<>>::value,
                std::tuple<ambiguous_type>,
                filtered_args
            >::type;
        };

        template <class ...T> struct common_type;
 
        template <class T>
        struct common_type<T> {
            using type = T;
        };
         
        template <class T, class U>
        struct common_type<T, U> {

            using type = typename std::conditional<
                std::is_convertible<T, U>::value,
                U,
                typename std::conditional<
                    std::is_convertible<U, T>::value,
                    T,
                    decltype(true ? std::declval<T>() : std::declval<U>())
                >::type
            >::type;
        };
         
        template <class T, class U, class... V>
        struct common_type<T, U, V...> {
            using type = typename common_type<typename common_type<T, U>::type, V...>::type;
        };

        template<typename Tup>
        struct custom_common_type;

        template<typename... Ts>
        struct custom_common_type<std::tuple<Ts...>> {
            using type = typename common_type<Ts...>::type;
        };

        template<typename Tup>
        struct common_expected_arg_types;

        template<typename... PhRoutes, typename... OtherGroupTuples>
        struct common_expected_arg_types<std::tuple<std::tuple<PhRoutes...>, OtherGroupTuples...>> {

            using expected_types = std::tuple<
                typename std::tuple_element<
                    PhRoutes::original_arg_index,
                    typename PhRoutes::expression::original_args
                >::type...
            >;

            using type = typename prepend<
                typename custom_common_type<typename valid_args<expected_types>::type>::type,
                typename common_expected_arg_types<std::tuple<OtherGroupTuples...>>::type
            >::type;
        };

        template<>
        struct common_expected_arg_types<std::tuple<>> {
            using type = std::tuple<>;
        };

        template<typename BindExpr>
        struct bind_expression_parser;

        template<typename Callable, typename... Args>
        struct bind_expression_parser<bind_expression<Callable, Args...>> {

            using root_expression = bind_expression<Callable, Args...>;

            using flattened_bind_expressions =
                typename root_expression::flattened_bind_expressions;

            using placeholder_routes = typename combined_placeholder_routes<
                flattened_bind_expressions
            >::type;

            using grouped_placeholders = tuple_group_by<
                placeholder_routes,
                ph_value_wrapper
            >;

            using arg_types = typename common_expected_arg_types<grouped_placeholders>::type;
        };
    }
}

#endif