/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_BIND_EXPRESSION_TRAITS_HPP
#define CALLABLE_TRAITS_BIND_EXPRESSION_TRAITS_HPP

#include <callable_traits/fwd/bind_expression_parser_fwd.hpp>

namespace callable_traits {

    namespace ctdetail {

        template<typename BindExpr>
        struct bind_expression_traits {

            using parser = bind_expression_parser<BindExpr>;
            static constexpr const bool value = parser::value;
            using traits = bind_expression_traits;
            using arg_types = typename parser::arg_types;
            using return_type = typename parser::return_type;
            using function_type = typename parser::function_type;
            using abominable_type = typename parser::abominable_type;

        };
    }
}

#endif
