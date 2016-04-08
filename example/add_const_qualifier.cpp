/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ add_const_qualifier
#include <type_traits>
#include <callable_traits/add_const_qualifier.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() const;
        using test = ct::add_const_qualifier<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_const_qualifier doesn't change anything when
        // the function type is already const.
        using pmf = void(foo::*)() const &&;
        using expect = void(foo::*)() const &&;
        using test = ct::add_const_qualifier<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        using pmf = void(foo::*)() volatile &;
        using expect = void(foo::*)() const volatile &;
        using test = ct::add_const_qualifier<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_const_qualifier can also be used to create "abominable"
        // function types.
        using f = void();
        using expect = void() const;
        using test = ct::add_const_qualifier<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_const_qualifier has no affect on function pointers,
        // function references, function objects, or member data pointers.
        using f = void(*)();
        using expect = void(*)();
        using test = ct::add_const_qualifier<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]
