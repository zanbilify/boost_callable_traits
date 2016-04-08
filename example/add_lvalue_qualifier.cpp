/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ add_lvalue_qualifier
#include <type_traits>
#include <callable_traits/add_lvalue_qualifier.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() &;
        using test = ct::add_lvalue_qualifier<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_lvalue_qualifier doesn't change anything when
        // the function type already has an lvalue qualifier.
        using pmf = void(foo::*)() &;
        using expect = void(foo::*)() &;
        using test = ct::add_lvalue_qualifier<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_lvalue_qualifier models C++11 reference collapsing
        // rules, so that adding an lvalue qualifier to an
        // rvalue-qualified type will force the lvalue.
        using pmf = void(foo::*)() &&;
        using expect = void(foo::*)() &;
        using test = ct::add_lvalue_qualifier<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_lvalue_qualifier can also be used to create "abominable"
        // function types.
        using f = void();
        using expect = void() &;
        using test = ct::add_lvalue_qualifier<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_lvalue_qualifier has no affect on function pointers,
        // function references, function objects, or member data pointers.
        using f = int foo::*;
        using expect = int foo::*;
        using test = ct::add_lvalue_qualifier<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]
