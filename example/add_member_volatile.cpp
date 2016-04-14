/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ add_member_volatile
#include <type_traits>
#include <callable_traits/add_member_volatile.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() volatile;
        using test = ct::add_member_volatile<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_volatile doesn't change anything when
        // the function type is already volatile.
        using pmf = void(foo::*)() volatile &&;
        using expect = void(foo::*)() volatile &&;
        using test = ct::add_member_volatile<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        using pmf = void(foo::*)() const &;
        using expect = void(foo::*)() const volatile &;
        using test = ct::add_member_volatile<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_volatile can also be used with "abominable"
        // function types.
        using f = void();
        using expect = void() volatile;
        using test = ct::add_member_volatile<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_volatile does not compile with function pointers,
        // function references, function objects, or member data pointers.
        // However, you can loosen this restriction somewhat by using the
        // callable_traits::permissive namespace instead:
        using f = void(*)();
        using expect = f;
        using test = ct::permissive::add_member_volatile<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]
