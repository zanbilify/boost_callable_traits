/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ add_function_const
#include <type_traits>
#include <callable_traits/add_function_const.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() const;
        using test = ct::add_function_const<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_const doesn't change anything when
        // the function type is already const.
        using pmf = void(foo::*)() const &&;
        using expect = void(foo::*)() const &&;
        using test = ct::add_function_const<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        using pmf = void(foo::*)() volatile &;
        using expect = void(foo::*)() const volatile &;
        using test = ct::add_function_const<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_const can also be used with "abominable"
        // function types.
        using f = void();
        using expect = void() const;
        using test = ct::add_function_const<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_const has no affect on function pointers,
        // function references, function objects, or member data pointers.
        using f = void(*)();
        using expect = void(*)();
        using test = ct::add_function_const<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]
