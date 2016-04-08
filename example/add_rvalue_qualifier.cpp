/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ add_rvalue_qualifier
#include <type_traits>
#include <callable_traits/add_rvalue_qualifier.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() &&;
        using test = ct::add_rvalue_qualifier<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_rvalue_qualifier doesn't change anything when
        // the function type already has an rvalue qualifier.
        using pmf = void(foo::*)() &&;
        using expect = void(foo::*)() &&;
        using test = ct::add_rvalue_qualifier<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_rvalue_qualifier models C++11 reference collapsing
        // rules, so that adding an rvalue qualifier to an
        // lvalue-qualified type will not change anything.
        using pmf = void(foo::*)() const &;
        using expect = void(foo::*)() const &;
        using test = ct::add_rvalue_qualifier<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_rvalue_qualifier can also be used with "abominable"
        // function types.
        using f = void() const;
        using expect = void() const &&;
        using test = ct::add_rvalue_qualifier<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_rvalue_qualifier has no affect on function pointers,
        // function references, function objects, or member data pointers.
        auto lambda = []{};
        using lambda_t = decltype(lambda);
        using expect = lambda_t;
        using test = ct::add_rvalue_qualifier<lambda_t>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]

