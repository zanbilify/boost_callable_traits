/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <utility>
#include <callable_traits/has_varargs.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
#define LREF
#define RREF
#else
#define LREF &
#define RREF &&
#endif

struct foo {};

namespace ct = callable_traits;

template<typename T>
void assert_has_varargs() {

    CT_ASSERT(ct::has_varargs<T>());
    CT_ASSERT(ct::has_varargs<T&>());
    CT_ASSERT(ct::has_varargs<T &&>());
    CT_ASSERT(ct::has_varargs<T const>());
    CT_ASSERT(ct::has_varargs<T const &>());
    CT_ASSERT(ct::has_varargs<T const &&>());
    CT_ASSERT(ct::has_varargs<T volatile>());
    CT_ASSERT(ct::has_varargs<T volatile &>());
    CT_ASSERT(ct::has_varargs<T volatile &&>());
    CT_ASSERT(ct::has_varargs<T const volatile &>());
    CT_ASSERT(ct::has_varargs<T const volatile &&>());

    CT_ASSERT(decltype(ct::has_varargs(std::declval<T>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T&>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T &&>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T const>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T const &>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T const &&>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T volatile>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T volatile &>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T volatile &&>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T const volatile &>()))::value);
    CT_ASSERT(decltype(ct::has_varargs(std::declval<T const volatile &&>()))::value);
}


template<typename T>
void assert_not_has_varargs() {

    CT_ASSERT(!ct::has_varargs<T>());
    CT_ASSERT(!ct::has_varargs<T&>());
    CT_ASSERT(!ct::has_varargs<T &&>());
    CT_ASSERT(!ct::has_varargs<T const>());
    CT_ASSERT(!ct::has_varargs<T const &>());
    CT_ASSERT(!ct::has_varargs<T const &&>());
    CT_ASSERT(!ct::has_varargs<T volatile>());
    CT_ASSERT(!ct::has_varargs<T volatile &>());
    CT_ASSERT(!ct::has_varargs<T volatile &&>());
    CT_ASSERT(!ct::has_varargs<T const volatile &>());
    CT_ASSERT(!ct::has_varargs<T const volatile &&>());

    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T&>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T &&>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T const>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T const &>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T const &&>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T volatile>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T volatile &>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T volatile &&>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T const volatile &>()))::value);
    CT_ASSERT(!decltype(ct::has_varargs(std::declval<T const volatile &&>()))::value);
}


int main() {

    {
        using f   = void(foo::*)();
        using l   = void(foo::*)() LREF;
        using r   = void(foo::*)() RREF ;
        using c   = void(foo::*)() const;
        using cl  = void(foo::*)() const LREF;
        using cr  = void(foo::*)() const RREF;
        using v   = void(foo::*)() volatile;
        using vl  = void(foo::*)() volatile LREF;
        using vr  = void(foo::*)() volatile RREF;
        using cv  = void(foo::*)() const volatile;
        using cvl = void(foo::*)() const volatile LREF;
        using cvr = void(foo::*)() const volatile RREF;

        assert_not_has_varargs<f>();
        assert_not_has_varargs<l>();
        assert_not_has_varargs<r>();
        assert_not_has_varargs<c>();
        assert_not_has_varargs<cl>();
        assert_not_has_varargs<cr>();
        assert_not_has_varargs<v>();
        assert_not_has_varargs<vl>();
        assert_not_has_varargs<vr>();
        assert_not_has_varargs<cv>();
        assert_not_has_varargs<cvl>();
        assert_not_has_varargs<cvr>();
    }

    {
        using f   = int foo::*;
        using l   = int foo::* LREF;
        using r   = int foo::* RREF ;
        using c   = int foo::* const;
        using cl  = int foo::* const LREF;
        using cr  = int foo::* const RREF;
        using v   = int foo::* volatile;
        using vl  = int foo::* volatile LREF;
        using vr  = int foo::* volatile RREF;
        using cv  = int foo::* const volatile;
        using cvl = int foo::* const volatile LREF;
        using cvr = int foo::* const volatile RREF;

        assert_not_has_varargs<f>();
        assert_not_has_varargs<l>();
        assert_not_has_varargs<r>();
        assert_not_has_varargs<c>();
        assert_not_has_varargs<cl>();
        assert_not_has_varargs<cr>();
        assert_not_has_varargs<v>();
        assert_not_has_varargs<vl>();
        assert_not_has_varargs<vr>();
        assert_not_has_varargs<cv>();
        assert_not_has_varargs<cvl>();
        assert_not_has_varargs<cvr>();
    }

    {
        //a member data pointer to a function pointer
        //is not treated like a member function pointer
        using f_ptr = void(*)(...);

        using f   = f_ptr foo::*;
        using l   = f_ptr foo::* &;
        using r   = f_ptr foo::* && ;
        using c   = f_ptr foo::* const;
        using cl  = f_ptr foo::* const &;
        using cr  = f_ptr foo::* const &&;
        using v   = f_ptr foo::* volatile;
        using vl  = f_ptr foo::* volatile &;
        using vr  = f_ptr foo::* volatile &&;
        using cv  = f_ptr foo::* const volatile;
        using cvl = f_ptr foo::* const volatile &;
        using cvr = f_ptr foo::* const volatile &&;

        assert_not_has_varargs<f>();
        assert_not_has_varargs<l>();
        assert_not_has_varargs<r>();
        assert_not_has_varargs<c>();
        assert_not_has_varargs<cl>();
        assert_not_has_varargs<cr>();
        assert_not_has_varargs<v>();
        assert_not_has_varargs<vl>();
        assert_not_has_varargs<vr>();
        assert_not_has_varargs<cv>();
        assert_not_has_varargs<cvl>();
        assert_not_has_varargs<cvr>();
    }

    {
        using f   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...);
        using l   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) LREF;
        using r   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) RREF ;
        using c   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const;
        using cl  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const LREF;
        using cr  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const RREF;
        using v   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) volatile;
        using vl  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) volatile LREF;
        using vr  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) volatile RREF;
        using cv  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const volatile;
        using cvl = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const volatile LREF;
        using cvr = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const volatile RREF;

        assert_has_varargs<f>();
        assert_has_varargs<l>();
        assert_has_varargs<r>();
        assert_has_varargs<c>();
        assert_has_varargs<cl>();
        assert_has_varargs<cr>();
        assert_has_varargs<v>();
        assert_has_varargs<vl>();
        assert_has_varargs<vr>();
        assert_has_varargs<cv>();
        assert_has_varargs<cvl>();
        assert_has_varargs<cvr>();
    }

    {
        struct f   { int operator()() { return 0; } };
        struct l   { int operator()() LREF { return 0; } };
        struct r   { int operator()() RREF { return 0; } };
        struct c   { int operator()() const { return 0; } };
        struct cl  { int operator()() const LREF { return 0; } };
        struct cr  { int operator()() const RREF { return 0; } };
        struct v   { int operator()() volatile { return 0; } };
        struct vl  { int operator()() volatile LREF { return 0; } };
        struct vr  { int operator()() volatile RREF { return 0; } };
        struct cv  { int operator()() const volatile { return 0; } };
        struct cvl { int operator()() const volatile LREF { return 0; } };
        struct cvr { int operator()() const volatile RREF { return 0; } };

        assert_not_has_varargs<f>();
        assert_not_has_varargs<l>();
        assert_not_has_varargs<r>();
        assert_not_has_varargs<c>();
        assert_not_has_varargs<cl>();
        assert_not_has_varargs<cr>();
        assert_not_has_varargs<v>();
        assert_not_has_varargs<vl>();
        assert_not_has_varargs<vr>();
        assert_not_has_varargs<cv>();
        assert_not_has_varargs<cvl>();
        assert_not_has_varargs<cvr>();
    }

    {
        struct f   { int operator()(...) { return 0; } };
        struct l   { int operator()(...) LREF { return 0; } };
        struct r   { int operator()(...) RREF { return 0; } };
        struct c   { int operator()(...) const { return 0; } };
        struct cl  { int operator()(...) const LREF { return 0; } };
        struct cr  { int operator()(...) const RREF { return 0; } };
        struct v   { int operator()(...) volatile { return 0; } };
        struct vl  { int operator()(...) volatile LREF { return 0; } };
        struct vr  { int operator()(...) volatile RREF { return 0; } };
        struct cv  { int operator()(...) const volatile { return 0; } };
        struct cvl { int operator()(...) const volatile LREF { return 0; } };
        struct cvr { int operator()(...) const volatile RREF { return 0; } };

        assert_has_varargs<f>();
        assert_has_varargs<l>();
        assert_has_varargs<r>();
        assert_has_varargs<c>();
        assert_has_varargs<cl>();
        assert_has_varargs<cr>();
        assert_has_varargs<v>();
        assert_has_varargs<vl>();
        assert_has_varargs<vr>();
        assert_has_varargs<cv>();
        assert_has_varargs<cvl>();
        assert_has_varargs<cvr>();
    }

#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

    {
        using f   = void();
        using l   = void() LREF;
        using r   = void() RREF ;
        using c   = void() const;
        using cl  = void() const LREF;
        using cr  = void() const RREF;
        using v   = void() volatile;
        using vl  = void() volatile LREF;
        using vr  = void() volatile RREF;
        using cv  = void() const volatile;
        using cvl = void() const volatile LREF;
        using cvr = void() const volatile RREF;

        CT_ASSERT(!ct::has_varargs<f>());
        CT_ASSERT(!ct::has_varargs<l>());
        CT_ASSERT(!ct::has_varargs<r>());
        CT_ASSERT(!ct::has_varargs<c>());
        CT_ASSERT(!ct::has_varargs<cl>());
        CT_ASSERT(!ct::has_varargs<cr>());
        CT_ASSERT(!ct::has_varargs<v>());
        CT_ASSERT(!ct::has_varargs<vl>());
        CT_ASSERT(!ct::has_varargs<vr>());
        CT_ASSERT(!ct::has_varargs<cv>());
        CT_ASSERT(!ct::has_varargs<cvl>());
        CT_ASSERT(!ct::has_varargs<cvr>());
    }

    {
        using f   = void(...);
        using l   = void(...) LREF;
        using r   = void(...) RREF ;
        using c   = void(...) const;
        using cl  = void(...) const LREF;
        using cr  = void(...) const RREF;
        using v   = void(...) volatile;
        using vl  = void(...) volatile LREF;
        using vr  = void(...) volatile RREF;
        using cv  = void(...) const volatile;
        using cvl = void(...) const volatile LREF;
        using cvr = void(...) const volatile RREF;

        CT_ASSERT(ct::has_varargs<f>());
        CT_ASSERT(ct::has_varargs<l>());
        CT_ASSERT(ct::has_varargs<r>());
        CT_ASSERT(ct::has_varargs<c>());
        CT_ASSERT(ct::has_varargs<cl>());
        CT_ASSERT(ct::has_varargs<cr>());
        CT_ASSERT(ct::has_varargs<v>());
        CT_ASSERT(ct::has_varargs<vl>());
        CT_ASSERT(ct::has_varargs<vr>());
        CT_ASSERT(ct::has_varargs<cv>());
        CT_ASSERT(ct::has_varargs<cvl>());
        CT_ASSERT(ct::has_varargs<cvr>());
    }

#endif //#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

    assert_not_has_varargs<void(*)()>();
    assert_has_varargs<void(*)(...)>();
    assert_not_has_varargs<void(&)()>();
    assert_has_varargs<void(&)(...)>();
}
