/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ add_cv_qualifiers
#include <type_traits>
#include <callable_traits/add_cv_qualifiers.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() const volatile;
        using test = ct::add_cv_qualifiers<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_cv_qualifiers doesn't change anything when
        // the function type is already cv-qualified.
        using pmf = void(foo::*)() const volatile &&;
        using expect = void(foo::*)() const volatile &&;
        using test = ct::add_cv_qualifiers<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        using pmf = void(foo::*)() volatile &;
        using expect = void(foo::*)() const volatile &;
        using test = ct::add_cv_qualifiers<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_cv_qualifiers can also be used with "abominable"
        // function types.
        using f = void();
        using expect = void() const volatile;
        using test = ct::add_cv_qualifiers<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_cv_qualifiers has no affect on function pointers,
        // function references, function objects, or member data pointers.
        using f = void(&)();
        using expect = void(&)();
        using test = ct::add_cv_qualifiers<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]
