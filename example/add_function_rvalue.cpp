/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ add_function_rvalue
#include <type_traits>
#include <callable_traits/add_function_rvalue.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() &&;
        using test = ct::add_function_rvalue<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_rvalue doesn't change anything when
        // the function type already has an rvalue qualifier.
        using pmf = void(foo::*)() &&;
        using expect = void(foo::*)() &&;
        using test = ct::add_function_rvalue<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_rvalue models C++11 reference collapsing
        // rules, so that adding an rvalue qualifier to an
        // lvalue-qualified type will not change anything.
        using pmf = void(foo::*)() const &;
        using expect = void(foo::*)() const &;
        using test = ct::add_function_rvalue<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_rvalue can also be used with "abominable"
        // function types.
        using f = void() const;
        using expect = void() const &&;
        using test = ct::add_function_rvalue<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_function_rvalue does not compile with function pointers,
        // function references, function objects, or member data pointers.
        // However, you can loosen this restriction somewhat by using the
        // callable_traits::permissive namespace instead:
        using f = void(*)();
        using expect = f;
        using test = ct::permissive::add_function_rvalue<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]

