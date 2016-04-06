#include <functional>
#include <callable_traits/callable_traits.hpp>

#ifndef EXAMPLE_ADAPTORS_HPP
#define EXAMPLE_ADAPTORS_HPP

namespace example {

    namespace ct = callable_traits;

    //`make_function` turns any (non-overloaded) callable into std::function
    template<typename T>
    inline decltype(auto) make_function(T&& t) {
        using signature = ct::function_type<T&&>;
        using result_type = std::function<signature>;
        return result_type{ ::std::forward<T>(t) };
    }

    //this `make_function` overload turns a bind expression into std::function
    template<typename T, typename First, typename... Others>
    inline decltype(auto) make_function(T&& t, First&& first, Others&&... others) {

        using bind_expr = decltype(::callable_traits::bind(
            ::std::forward<T>(t),
            ::std::forward<First>(first),
            ::std::forward<Others>(others)...
        ));

        using signature = ct::function_type<bind_expr>;
        using result_type = std::function<signature>;

        return result_type{ ::std::bind(
            ::std::forward<T>(t),
            ::std::forward<First>(first),
            ::std::forward<Others>(others)...
        )};
    }
}

#endif
