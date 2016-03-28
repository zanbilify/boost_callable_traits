/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_BIND_EXPRESSION_PARSER_HPP
#define CALLABLE_TRAITS_BIND_EXPRESSION_PARSER_HPP

#include <callable_traits/traits.hpp>
#include <callable_traits/tuple_group_by.hpp>
#include <callable_traits/tuple_sort.hpp>
#include <callable_traits/bind_expression.hpp>
#include <callable_traits/fwd/bind_expression_parser_fwd.hpp>
#include <callable_traits/best_match.hpp>
#include <callable_traits/prepend.hpp>
#include <tuple>
#include <functional>

namespace callable_traits {
    
    namespace detail {

        template<typename BindExpressionTuple>
        struct combine_placeholder_routes;

        template<typename... BindExprs>
        struct combine_placeholder_routes<std::tuple<BindExprs...>> {

            using placeholder_route_map = decltype(std::tuple_cat(std::declval<
                typename placeholder_routes<
                    BindExprs,
                    typename BindExprs::bind_args_tuple
            >::type>()...));

            using type = tuple_sort<
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
                && !std::is_same<Head, unknown>{}
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
                std::tuple<unknown>,
                filtered_args
            >::type;
        };

        template<typename Tup>
        struct find_best_match;

        template<typename... Ts>
        struct find_best_match<std::tuple<Ts...>> {
            using type = best_match<Ts...>;
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
                typename find_best_match<typename valid_args<expected_types>::type>::type,
                typename common_expected_arg_types<std::tuple<OtherGroupTuples...>>::type
            >::type;
        };

        template<>
        struct common_expected_arg_types<std::tuple<>> {
            using type = std::tuple<>;
        };

        template<typename...>
        struct build_function {};

        template<typename Return, typename... Args>
        struct build_function<Return, std::tuple<Args...>>{
            using type = Return(Args...);
        };

        template<typename T>
        struct bind_expression_parser
        {
            static constexpr const bool value = false;
            using arg_types = invalid_type;
            using return_type = invalid_type;
            using function_type = invalid_type;
            using abominable_type = invalid_type;
        };

        template<typename Callable, typename... Args>
        struct bind_expression_parser<bind_expression<Callable, Args...>> {

            static constexpr const bool value = true;

            using root_expression = bind_expression<Callable, Args...>;

            using flattened_bind_expressions =
                typename root_expression::flattened_bind_expressions;

            using placeholder_routes = typename combine_placeholder_routes<
                flattened_bind_expressions
            >::type;

            using grouped_placeholders = tuple_group_by<
                placeholder_routes,
                ph_value_wrapper
            >;

            using arg_types = typename common_expected_arg_types<grouped_placeholders>::type;
            using return_type = typename root_expression::return_type;
            using function_type = typename build_function<return_type, arg_types>::type;
            using abominable_type = function_type;
        };
    }
}

#endif
