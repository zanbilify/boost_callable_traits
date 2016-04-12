/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <utility>
#include <callable_traits/is_qualified.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo {};

namespace ct = callable_traits;

template<typename T>
void assert_qualified() {
    CT_ASSERT(ct::is_qualified<T>());
    CT_ASSERT(ct::is_qualified<T&>());
    CT_ASSERT(ct::is_qualified<T &&>());
    CT_ASSERT(ct::is_qualified<T const>());
    CT_ASSERT(ct::is_qualified<T const &>());
    CT_ASSERT(ct::is_qualified<T const &&>());
    CT_ASSERT(ct::is_qualified<T volatile>());
    CT_ASSERT(ct::is_qualified<T volatile &>());
    CT_ASSERT(ct::is_qualified<T volatile &&>());
    CT_ASSERT(ct::is_qualified<T const volatile &>());
    CT_ASSERT(ct::is_qualified<T const volatile &&>());

    CT_ASSERT(decltype(ct::is_qualified(std::declval<T>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T&>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T &&>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T const>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T const &>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T const &&>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T volatile>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T volatile &>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T volatile &&>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T const volatile &>()))::value);
    CT_ASSERT(decltype(ct::is_qualified(std::declval<T const volatile &&>()))::value);
}


template<typename T>
void assert_unqualified() {
    CT_ASSERT(!ct::is_qualified<T>());
    CT_ASSERT(!ct::is_qualified<T&>());
    CT_ASSERT(!ct::is_qualified<T &&>());
    CT_ASSERT(!ct::is_qualified<T const>());
    CT_ASSERT(!ct::is_qualified<T const &>());
    CT_ASSERT(!ct::is_qualified<T const &&>());
    CT_ASSERT(!ct::is_qualified<T volatile>());
    CT_ASSERT(!ct::is_qualified<T volatile &>());
    CT_ASSERT(!ct::is_qualified<T volatile &&>());
    CT_ASSERT(!ct::is_qualified<T const volatile &>());
    CT_ASSERT(!ct::is_qualified<T const volatile &&>());

    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T&>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T &&>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T const>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T const &>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T const &&>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T volatile>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T volatile &>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T volatile &&>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T const volatile &>()))::value);
    CT_ASSERT(!decltype(ct::is_qualified(std::declval<T const volatile &&>()))::value);
}

int main() {

    {
        using f   = void(foo::*)();
        using l   = void(foo::*)() &;
        using r   = void(foo::*)() && ;
        using c   = void(foo::*)() const;
        using cl  = void(foo::*)() const &;
        using cr  = void(foo::*)() const &&;
        using v   = void(foo::*)() volatile;
        using vl  = void(foo::*)() volatile &;
        using vr  = void(foo::*)() volatile &&;
        using cv  = void(foo::*)() const volatile;
        using cvl = void(foo::*)() const volatile &;
        using cvr = void(foo::*)() const volatile &&;

        assert_unqualified<f>();
        assert_qualified<l>();
        assert_qualified<r>();
        assert_qualified<c>();
        assert_qualified<cl>();
        assert_qualified<cr>();
        assert_qualified<v>();
        assert_qualified<vl>();
        assert_qualified<vr>();
        assert_qualified<cv>();
        assert_qualified<cvl>();
        assert_qualified<cvr>();
    }

    {
        struct f   { int operator()() { return 0; } };
        struct l   { int operator()() & { return 0; } };
        struct r   { int operator()() && { return 0; } };
        struct c   { int operator()() const { return 0; } };
        struct cl  { int operator()() const & { return 0; } };
        struct cr  { int operator()() const && { return 0; } };
        struct v   { int operator()() volatile { return 0; } };
        struct vl  { int operator()() volatile & { return 0; } };
        struct vr  { int operator()() volatile && { return 0; } };
        struct cv  { int operator()() const volatile { return 0; } };
        struct cvl { int operator()() const volatile & { return 0; } };
        struct cvr { int operator()() const volatile && { return 0; } };

        assert_unqualified<f>();
        assert_qualified<l>();
        assert_qualified<r>();
        assert_qualified<c>();
        assert_qualified<cl>();
        assert_qualified<cr>();
        assert_qualified<v>();
        assert_qualified<vl>();
        assert_qualified<vr>();
        assert_qualified<cv>();
        assert_qualified<cvl>();
        assert_qualified<cvr>();
    }

    {
        using f   = void();
        using l   = void() &;
        using r   = void() && ;
        using c   = void() const;
        using cl  = void() const &;
        using cr  = void() const &&;
        using v   = void() volatile;
        using vl  = void() volatile &;
        using vr  = void() volatile &&;
        using cv  = void() const volatile;
        using cvl = void() const volatile &;
        using cvr = void() const volatile &&;

        CT_ASSERT(!ct::is_qualified<f>());
        CT_ASSERT(ct::is_qualified<l>());
        CT_ASSERT(ct::is_qualified<r>());
        CT_ASSERT(ct::is_qualified<c>());
        CT_ASSERT(ct::is_qualified<cl>());
        CT_ASSERT(ct::is_qualified<cr>());
        CT_ASSERT(ct::is_qualified<v>());
        CT_ASSERT(ct::is_qualified<vl>());
        CT_ASSERT(ct::is_qualified<vr>());
        CT_ASSERT(ct::is_qualified<cv>());
        CT_ASSERT(ct::is_qualified<cvl>());
        CT_ASSERT(ct::is_qualified<cvr>());
    }

    assert_unqualified<void(*)()>();
    assert_unqualified<void(&)()>();
}
