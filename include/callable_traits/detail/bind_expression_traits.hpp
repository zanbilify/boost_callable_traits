/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_BIND_EXPRESSION_TRAITS_HPP
#define CALLABLE_TRAITS_DETAIL_BIND_EXPRESSION_TRAITS_HPP

#include <callable_traits/detail/fwd/bind_expression_parser_fwd.hpp>
#include <callable_traits/detail/default_callable_traits.hpp>

namespace callable_traits {

    namespace detail {

        namespace bind_expr_detail {

            template<typename, template<class...> class>
            struct expand_bind_args;

            template<typename... Args, template<class...> class Container>
            struct expand_bind_args<std::tuple<Args...>, Container> {
                using type = Container<Args...>;
            };
        }



        template<typename BindExpr>
        struct bind_expression_traits : default_callable_traits {

            using parser = bind_expression_parser<BindExpr>;
            static constexpr const bool value = parser::value;
            using traits = bind_expression_traits;
            using arg_types = typename parser::arg_types;
            using invoke_arg_types = arg_types;
            using return_type = typename parser::return_type;
            using function_type = typename parser::function_type;
            using qualified_function_type = typename parser::qualified_function_type;

            template<template<class...> class Container>
            using expand_args =
                typename bind_expr_detail::expand_bind_args<arg_types, Container>::type;

            template<template<class...> class Container>
            using expand_invoke_args =
                typename bind_expr_detail::expand_bind_args<arg_types, Container>::type;
        };
    }
}

#endif
