/*!
Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
Copyright (c) 2001 David Abrahams
Copyright (c) 2005 Peter Dimov
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_BIND_EXPRESSION_HPP
#define CALLABLE_TRAITS_DETAIL_BIND_EXPRESSION_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/categorize_bind_arg.hpp>
#include <callable_traits/detail/placeholder.hpp>
#include <callable_traits/detail/fwd/bind_expression_fwd.hpp>
#include <callable_traits/detail/utility.hpp>
//#include <callable_traits/detail/private_tuple.hpp>

#include <tuple>
#include <functional>

namespace callable_traits {
    
    namespace detail {

        template <typename T>
        struct is_callable_traits_bind
            : std::false_type {};

        template <typename Callable, typename... Args>
        struct is_callable_traits_bind<bind_expression<Callable, Args...>>
            : std::true_type {};

        template<typename PhRouteLeft, typename PhRouteRight>
        struct compare_ph_value {
            static constexpr bool value = 
                PhRouteLeft::ph_value < PhRouteRight::ph_value;
        };

        template <typename...> struct bind_expressions_filter;

        template <> struct bind_expressions_filter<> {
            using type = std::tuple<>;
        };

        template <typename Head, typename... Tail>
        struct bind_expressions_filter<Head, Tail...> {

            using filtered_tail = typename bind_expressions_filter<Tail...>::type;
            using decayed_head = shallow_decay<Head>;

            using type = typename std::conditional<
                is_callable_traits_bind<decayed_head>::value,
                typename prepend<decayed_head, filtered_tail>::type,
                filtered_tail
            >::type;
        };

        template <typename... Ts>
        struct remove_non_bind_expressions {
            using type = typename bind_expressions_filter<Ts...>::type;
        };

        template<typename T>
        struct is_empty_tuple : std::false_type{};

        template<>
        struct is_empty_tuple<std::tuple<>> : std::true_type{};

        template<typename T>
        struct is_not_empty_tuple : std::true_type {};

        template<>
        struct is_not_empty_tuple<std::tuple<>> : std::false_type {};

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
            typename is_not_empty_tuple<typename BindExpr::inner_bind_expressions>::type
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
            typename is_empty_tuple<typename BindExpr::inner_bind_expressions>::type
        > {
            using type = std::tuple<BindExpr>;
        };

        template<typename T, typename std::enable_if<
            is_callable_traits_bind<shallow_decay<T>>::value, int>::type = 0>
        inline constexpr CALLALBLE_TRAITS_DECLTYPE_AUTO
        unwrap_std_bind(T&& t){
            return t.get_std_bind();
        }

        template<typename T, typename std::enable_if<
            !is_callable_traits_bind<shallow_decay<T>>::value, int>::type = 0>
        inline constexpr T&& unwrap_std_bind(T&& t){
            return std::forward<T>(t);
        }

        template<typename Callable, typename... Args>
        struct bind_expression {

            private:

            using bind_type = typename std::remove_reference<decltype(
                std::bind(std::declval<Callable>(), unwrap_std_bind(std::declval<Args>())...)
            )>::type;

            bind_type std_bind;

            public:

            using bind_args_tuple = std::tuple<
                typename categorize_bind_arg<
                    Args,
                    typename std::remove_reference<Args>::type
                >::type...
            >;

            using inner_bind_expressions =
                typename remove_non_bind_expressions<Args...>::type;

            using flattened_bind_expressions =
                typename flatten_bind_expressions<bind_expression>::type;

            using placeholder_route_map = typename placeholder_routes<
                bind_expression,
                bind_args_tuple
            >::type;

            using original_args = typename traits<Callable>::invoke_arg_types;
            using return_type = typename traits<Callable>::return_type;
            using result_type = return_type;

#ifndef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

            inline bind_type&
            get_std_bind() & {
                return std_bind;
            }

            inline bind_type&&
            get_std_bind() && {
                return std::move(std_bind);
            }

#endif //#ifndef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

            inline constexpr
            bind_expression(Callable c, Args... args)
                : std_bind(
                    std::bind(static_cast<Callable>(c),
                        unwrap_std_bind(static_cast<Args>(args))...)) {}

            template<typename... Rgs>
            inline CALLALBLE_TRAITS_DECLTYPE_AUTO
            operator()(Rgs&&... args) {
                return std_bind(std::forward<Rgs>(args)...);
            }

            inline operator bind_type&() {
                return std_bind;
            }
        };

    }
}

#endif
