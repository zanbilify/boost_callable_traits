/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ add_varargs
#include <type_traits>
#include <callable_traits/add_varargs.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using f = void(int);
        using expect = void(int, ...);
        using test = ct::add_varargs<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        using fp = void(*)();
        using expect = void(*)(...);
        using test = ct::add_varargs<fp>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        using fr = void(&)(const char*);
        using expect = void(&)(const char*, ...);
        using test = ct::add_varargs<fr>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        using pmf = void(foo::*)() const;
        using expect = void(foo::*)(...) const;
        using test = ct::add_varargs<pmf>;
        static_assert(std::is_same<test, expect>::value, "");

        // add_varargs doesn't change anything when
        // the type already has varargs.
        using twice = ct::add_varargs<test>;
        static_assert(std::is_same<test, twice>::value, "");
    }

    // add_varargs fails in a SFINAE-friendly manner when
    // used on a function object or a member data pointer.
    //
    // {
    //     using d = int foo::*;
    //     using test = ct::add_varargs<d>;
    // }
    //
    // The error message is about as obvious as it can be without
    // resorting to a SFINAE-unfriendly static_assert (namespaces
    // omitted for brevity):
    //
    //   error: no type named 'type' in 'struct disjunction<
    //   type_value<invalid_type, false>, add_varargs_error<0> >'
}
//]
