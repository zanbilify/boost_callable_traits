/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ make_function_header

#ifndef EXAMPLE_MAKE_FUNCTION_HPP
#define EXAMPLE_MAKE_FUNCTION_HPP

#include <functional>
#include <callable_traits/function_type.hpp>
#include <callable_traits/bind.hpp>

namespace example {

    namespace ct = callable_traits;

    // make_function turns a non-overloaded callable into a type-erased std::function object
    template<typename T>
    inline decltype(auto) make_function(T&& t) {

        // callable_traits::function_type decays any non-overloaded callable type to
        // a plain function type, which is structured in terms of INVOKE.

        using no_ref = typename std::remove_reference<T>::type;
        using f = ct::function_type<no_ref>;
        using result_type = std::function<f>;
        return result_type{ std::forward<T>(t) };
    }

    // this make_function overload turns a bind expression into a type-erased std::function object
    template<typename T, typename First, typename... Others>
    inline decltype(auto) make_function(T&& t, First&& first, Others&&... others) {

        // callable_traits::bind is essentially a compile-time parser of placeholder
        // expressions, for the purpose of retaining more type information than
        // std::bind normally allows - specifically, callable_traits::bind is used to
        // determine the de-facto signature of the std::bind return type, with special
        // considerations for conversions between reused placeholders and nested
        // placeholder expressions. For the sake of convenience, callable_traits::bind
        // is also a thin forwarding wrapper around std::bind (which is the only true
        // runtime element in CallableTraits).

        using bind_expr = decltype(ct::bind(
                std::forward<T>(t),
                std::forward<First>(first),
                std::forward<Others>(others)...
        ));

        using f = ct::function_type<bind_expr>;
        using result_type = std::function<f>;

        return result_type{ std::bind(
                std::forward<T>(t),
                std::forward<First>(first),
                std::forward<Others>(others)...
        )};
    }
}

#endif //#ifndef EXAMPLE_MAKE_FUNCTION_HPP
//]
