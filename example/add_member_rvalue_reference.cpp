/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>
#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
int main(){ return 0; }
#else

//[ add_member_rvalue_reference_t
#include <type_traits>
#include <callable_traits/add_member_rvalue_reference.hpp>

namespace ct = callable_traits;

struct foo {};

int main() {

    {
        using pmf = void(foo::*)();
        using expect = void(foo::*)() &&;
        using test = ct::add_member_rvalue_reference_t<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_rvalue_reference_t doesn't change anything when
        // the function type already has an rvalue qualifier.
        using pmf = void(foo::*)() &&;
        using expect = void(foo::*)() &&;
        using test = ct::add_member_rvalue_reference_t<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_rvalue_reference_t models C++11 reference collapsing
        // rules, so that adding an rvalue qualifier to an
        // lvalue-qualified type will not change anything.
        using pmf = void(foo::*)() const &;
        using expect = void(foo::*)() const &;
        using test = ct::add_member_rvalue_reference_t<pmf>;
        static_assert(std::is_same<test, expect>::value, "");
    } {
        // add_member_rvalue_reference_t can also be used with "abominable"
        // function types.
        using f = void() const;
        using expect = void() const &&;
        using test = ct::add_member_rvalue_reference_t<f>;
        static_assert(std::is_same<test, expect>::value, "");
    }

    // A substitution failure will occur if add_member_rvalue_reference_t
    // is used with function pointers, function references, function objects,
    // or member data pointers.
}

//]
#endif //#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
