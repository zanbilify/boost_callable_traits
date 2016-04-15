/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/bind.hpp>
#ifdef CALLABLE_TRAITS_MSVC
//feature is unsupported in MSVC
int main(){ return 0; };
#else

//[ make_function
#include <functional>
#include <callable_traits/function_type.hpp>
#include <callable_traits/bind.hpp>

namespace example_library {

    namespace ct = callable_traits;

    // make_function turns a non-overloaded callable into a type-erased std::function object
    template<typename T>
    inline decltype(auto) make_function(T&& t) {

        // callable_traits::function_type decays any non-overloaded callable type to
        // a plain function type, which is structured in terms of INVOKE.

        using f = ct::function_type<T&&>;
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

// client code starts here
#include <cassert>

using namespace example_library;
using namespace std::placeholders;

int add(int i, int j) {
    return i + j;
}

struct adder {

    int eval(int i, int j) const {
        return i + j;
    }
};

int main() {

    // function pointer
    auto f = make_function(&add);
    assert(f(99, 1) == 100);

    // function reference
    f = make_function(add);
    assert(f(99, 1) == 100);

    // member function pointer (bound to object)
    f = make_function(&adder::eval, adder{}, _1, _2);
    assert(f(99, 1) == 100);

    // lambda
    f = make_function([](int i, int j) {
        return i + j;
    });

    assert(f(99, 1) == 100);
}
//]
#endif
