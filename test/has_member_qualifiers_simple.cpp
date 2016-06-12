/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <utility>
#include <callable_traits/has_member_qualifiers.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT


struct foo {};

namespace ct = callable_traits;

template<typename T>
void assert_qualified() {
    CT_ASSERT(ct::has_member_qualifiers<T>::value);
}

template<typename T>
void assert_unqualified() {
    CT_ASSERT(!ct::has_member_qualifiers<T>::value);
}

int main() {

    {
        using f   = void(foo::*)();
        using c   = void(foo::*)() const;
        using v   = void(foo::*)() volatile;
        using cv  = void(foo::*)() const volatile;

        assert_unqualified<f>();
        assert_qualified<c>();
        assert_qualified<v>();
        assert_qualified<cv>();
    }

    {
        struct f   { int operator()() { return 0; } };
        struct c   { int operator()() const { return 0; } };
        struct v   { int operator()() volatile { return 0; } };
        struct cv  { int operator()() const volatile { return 0; } };

        assert_unqualified<f>();
        assert_qualified<c>();
        assert_qualified<v>();
        assert_qualified<cv>();
    }

    using f_ptr = void(*)();
    assert_unqualified<f_ptr>();
    assert_unqualified<f_ptr foo::*>();
    assert_unqualified<int foo::*>();
    assert_unqualified<void(&)()>();
}
