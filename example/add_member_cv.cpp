/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>
#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
int main(){ return 0; }
#else

//[ add_member_cv
#include <type_traits>
#include <callable_traits/add_member_cv.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() const volatile;
        using test = ct::add_member_cv<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_cv doesn't change anything when
        // the function type is already cv-qualified.
        using pmf = void(foo::*)() const volatile &&;
        using expect = void(foo::*)() const volatile &&;
        using test = ct::add_member_cv<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        using pmf = void(foo::*)() volatile &;
        using expect = void(foo::*)() const volatile &;
        using test = ct::add_member_cv<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_cv can also be used with "abominable"
        // function types.
        using f = void();
        using expect = void() const volatile;
        using test = ct::add_member_cv<f>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_cv does not compile with function pointers,
        // function references, function objects, or member data pointers.
        // However, you can loosen this restriction somewhat by using the
        // callable_traits::permissive namespace instead:
        using f = void(*)();
        using expect = f;
        using test = ct::permissive::add_member_cv<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }
}
//]
#endif //#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
