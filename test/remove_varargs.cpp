/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/remove_varargs.hpp>

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

int main() {

    {
        using f      = void(foo::*)();
        using l      = void(foo::*)() LREF;
        using r      = void(foo::*)() RREF ;
        using c      = void(foo::*)() const;
        using cl     = void(foo::*)() const LREF;
        using cr     = void(foo::*)() const RREF;
        using v      = void(foo::*)() volatile;
        using vl     = void(foo::*)() volatile LREF;
        using vr     = void(foo::*)() volatile RREF;
        using cv     = void(foo::*)() const volatile;
        using cvl    = void(foo::*)() const volatile LREF;
        using cvr    = void(foo::*)() const volatile RREF;

        using va_f   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...);
        using va_l   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) LREF;
        using va_r   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) RREF ;
        using va_c   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const;
        using va_cl  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const LREF;
        using va_cr  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const RREF;
        using va_v   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) volatile;
        using va_vl  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) volatile LREF;
        using va_vr  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) volatile RREF;
        using va_cv  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const volatile;
        using va_cvl = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const volatile LREF;
        using va_cvr = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const volatile RREF;

        CT_ASSERT(std::is_same<f,   ct::remove_varargs<va_f>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_varargs<va_l>>{});
        CT_ASSERT(std::is_same<r,   ct::remove_varargs<va_r>>{});
        CT_ASSERT(std::is_same<c,   ct::remove_varargs<va_c>>{});
        CT_ASSERT(std::is_same<cl,  ct::remove_varargs<va_cl>>{});
        CT_ASSERT(std::is_same<cr,  ct::remove_varargs<va_cr>>{});
        CT_ASSERT(std::is_same<v,   ct::remove_varargs<va_v>>{});
        CT_ASSERT(std::is_same<vl,  ct::remove_varargs<va_vl>>{});
        CT_ASSERT(std::is_same<vr,  ct::remove_varargs<va_vr>>{});
        CT_ASSERT(std::is_same<cv,  ct::remove_varargs<va_cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::remove_varargs<va_cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::remove_varargs<va_cvr>>{});

        CT_ASSERT(std::is_same<f,   ct::remove_varargs<f>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_varargs<l>>{});
        CT_ASSERT(std::is_same<r,   ct::remove_varargs<r>>{});
        CT_ASSERT(std::is_same<c,   ct::remove_varargs<c>>{});
        CT_ASSERT(std::is_same<cl,  ct::remove_varargs<cl>>{});
        CT_ASSERT(std::is_same<cr,  ct::remove_varargs<cr>>{});
        CT_ASSERT(std::is_same<v,   ct::remove_varargs<v>>{});
        CT_ASSERT(std::is_same<vl,  ct::remove_varargs<vl>>{});
        CT_ASSERT(std::is_same<vr,  ct::remove_varargs<vr>>{});
        CT_ASSERT(std::is_same<cv,  ct::remove_varargs<cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::remove_varargs<cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::remove_varargs<cvr>>{});
    }

    {
        using f      = void(foo::*)(int&, int&&);
        using l      = void(foo::*)(int&, int&&) LREF;
        using r      = void(foo::*)(int&, int&&) RREF ;
        using c      = void(foo::*)(int&, int&&) const;
        using cl     = void(foo::*)(int&, int&&) const LREF;
        using cr     = void(foo::*)(int&, int&&) const RREF;
        using v      = void(foo::*)(int&, int&&) volatile;
        using vl     = void(foo::*)(int&, int&&) volatile LREF;
        using vr     = void(foo::*)(int&, int&&) volatile RREF;
        using cv     = void(foo::*)(int&, int&&) const volatile;
        using cvl    = void(foo::*)(int&, int&&) const volatile LREF;
        using cvr    = void(foo::*)(int&, int&&) const volatile RREF;

        using va_f   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...);
        using va_l   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) LREF;
        using va_r   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) RREF ;
        using va_c   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) const;
        using va_cl  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) const LREF;
        using va_cr  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) const RREF;
        using va_v   = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) volatile;
        using va_vl  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) volatile LREF;
        using va_vr  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) volatile RREF;
        using va_cv  = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) const volatile;
        using va_cvl = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) const volatile LREF;
        using va_cvr = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int&, int&&, ...) const volatile RREF;

        CT_ASSERT(std::is_same<f,   ct::remove_varargs<va_f>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_varargs<va_l>>{});
        CT_ASSERT(std::is_same<r,   ct::remove_varargs<va_r>>{});
        CT_ASSERT(std::is_same<c,   ct::remove_varargs<va_c>>{});
        CT_ASSERT(std::is_same<cl,  ct::remove_varargs<va_cl>>{});
        CT_ASSERT(std::is_same<cr,  ct::remove_varargs<va_cr>>{});
        CT_ASSERT(std::is_same<v,   ct::remove_varargs<va_v>>{});
        CT_ASSERT(std::is_same<vl,  ct::remove_varargs<va_vl>>{});
        CT_ASSERT(std::is_same<vr,  ct::remove_varargs<va_vr>>{});
        CT_ASSERT(std::is_same<cv,  ct::remove_varargs<va_cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::remove_varargs<va_cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::remove_varargs<va_cvr>>{});

        CT_ASSERT(std::is_same<f,   ct::remove_varargs<f>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_varargs<l>>{});
        CT_ASSERT(std::is_same<r,   ct::remove_varargs<r>>{});
        CT_ASSERT(std::is_same<c,   ct::remove_varargs<c>>{});
        CT_ASSERT(std::is_same<cl,  ct::remove_varargs<cl>>{});
        CT_ASSERT(std::is_same<cr,  ct::remove_varargs<cr>>{});
        CT_ASSERT(std::is_same<v,   ct::remove_varargs<v>>{});
        CT_ASSERT(std::is_same<vl,  ct::remove_varargs<vl>>{});
        CT_ASSERT(std::is_same<vr,  ct::remove_varargs<vr>>{});
        CT_ASSERT(std::is_same<cv,  ct::remove_varargs<cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::remove_varargs<cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::remove_varargs<cvr>>{});
    }

#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

    {
        using f      = void();
        using l      = void() LREF;
        using r      = void() RREF ;
        using c      = void() const;
        using cl     = void() const LREF;
        using cr     = void() const RREF;
        using v      = void() volatile;
        using vl     = void() volatile LREF;
        using vr     = void() volatile RREF;
        using cv     = void() const volatile;
        using cvl    = void() const volatile LREF;
        using cvr    = void() const volatile RREF;

        using va_f   = void(...);
        using va_l   = void(...) LREF;
        using va_r   = void(...) RREF ;
        using va_c   = void(...) const;
        using va_cl  = void(...) const LREF;
        using va_cr  = void(...) const RREF;
        using va_v   = void(...) volatile;
        using va_vl  = void(...) volatile LREF;
        using va_vr  = void(...) volatile RREF;
        using va_cv  = void(...) const volatile;
        using va_cvl = void(...) const volatile LREF;
        using va_cvr = void(...) const volatile RREF;

        CT_ASSERT(std::is_same<f,   ct::remove_varargs<va_f>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_varargs<va_l>>{});
        CT_ASSERT(std::is_same<r,   ct::remove_varargs<va_r>>{});
        CT_ASSERT(std::is_same<c,   ct::remove_varargs<va_c>>{});
        CT_ASSERT(std::is_same<cl,  ct::remove_varargs<va_cl>>{});
        CT_ASSERT(std::is_same<cr,  ct::remove_varargs<va_cr>>{});
        CT_ASSERT(std::is_same<v,   ct::remove_varargs<va_v>>{});
        CT_ASSERT(std::is_same<vl,  ct::remove_varargs<va_vl>>{});
        CT_ASSERT(std::is_same<vr,  ct::remove_varargs<va_vr>>{});
        CT_ASSERT(std::is_same<cv,  ct::remove_varargs<va_cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::remove_varargs<va_cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::remove_varargs<va_cvr>>{});

        CT_ASSERT(std::is_same<f,   ct::remove_varargs<f>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_varargs<l>>{});
        CT_ASSERT(std::is_same<r,   ct::remove_varargs<r>>{});
        CT_ASSERT(std::is_same<c,   ct::remove_varargs<c>>{});
        CT_ASSERT(std::is_same<cl,  ct::remove_varargs<cl>>{});
        CT_ASSERT(std::is_same<cr,  ct::remove_varargs<cr>>{});
        CT_ASSERT(std::is_same<v,   ct::remove_varargs<v>>{});
        CT_ASSERT(std::is_same<vl,  ct::remove_varargs<vl>>{});
        CT_ASSERT(std::is_same<vr,  ct::remove_varargs<vr>>{});
        CT_ASSERT(std::is_same<cv,  ct::remove_varargs<cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::remove_varargs<cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::remove_varargs<cvr>>{});
    }

#endif //#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

    {
        using f = void(&)();
        using va_f = void(&)(...);
        CT_ASSERT(std::is_same<f,   ct::remove_varargs<va_f>>{});
    }
}
