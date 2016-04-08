/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ add_function_lvalue
#include <type_traits>
#include <callable_traits/add_function_lvalue.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() &;
        using test = ct::add_function_lvalue<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_lvalue doesn't change anything when
        // the function type already has an lvalue qualifier.
        using pmf = void(foo::*)() &;
        using expect = void(foo::*)() &;
        using test = ct::add_function_lvalue<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_lvalue models C++11 reference collapsing
        // rules, so that adding an lvalue qualifier to an
        // rvalue-qualified type will force the lvalue.
        using pmf = void(foo::*)() &&;
        using expect = void(foo::*)() &;
        using test = ct::add_function_lvalue<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_lvalue can also be used to create "abominable"
        // function types.
        using f = void();
        using expect = void() &;
        using test = ct::add_function_lvalue<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_lvalue does not compile with function pointers,
        // function references, function objects, or member data pointers.
        // However, you can loosen this restriction somewhat by using the
        // callable_traits::permissive namespace instead:
        using f = void(*)();
        using expect = f;
        using test = ct::permissive::add_function_lvalue<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]
