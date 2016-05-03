/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/callable_traits.hpp>

#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
int main(){ return 0; }
#else

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo{};

namespace ct = callable_traits;

int main() {
    {
        using f   = void(foo::*)();
        using l   = void(foo::*)() &;
        using r   = void(foo::*)() &&;
        using c   = void(foo::*)() const;
        using cl  = void(foo::*)() const &;
        using cr  = void(foo::*)() const &&;
        using v   = void(foo::*)() volatile;
        using vl  = void(foo::*)() volatile &;
        using vr  = void(foo::*)() volatile &&;
        using cv  = void(foo::*)() const volatile;
        using cvl = void(foo::*)() const volatile &;
        using cvr = void(foo::*)() const volatile &&;

        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<f>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<c>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<v>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cv>>{});
        CT_ASSERT(std::is_same<l,   ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cl,  ct::add_member_rvalue_reference<cl>>{});
        CT_ASSERT(std::is_same<vl,  ct::add_member_rvalue_reference<vl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_member_rvalue_reference<cvl>>{});
        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<r>>{});
        CT_ASSERT(!std::is_same<r,  ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<cr>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<vr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cvr>>{});
    }

    {
        using f   = void(foo::*&)();
        using l   = void(foo::*&)() &;
        using r   = void(foo::*&)() &&;
        using c   = void(foo::*&)() const;
        using cl  = void(foo::*&)() const &;
        using cr  = void(foo::*&)() const &&;
        using v   = void(foo::*&)() volatile;
        using vl  = void(foo::*&)() volatile &;
        using vr  = void(foo::*&)() volatile &&;
        using cv  = void(foo::*&)() const volatile;
        using cvl = void(foo::*&)() const volatile &;
        using cvr = void(foo::*&)() const volatile &&;

        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<f>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<c>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<v>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cv>>{});
        CT_ASSERT(std::is_same<l,   ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cl,  ct::add_member_rvalue_reference<cl>>{});
        CT_ASSERT(std::is_same<vl,  ct::add_member_rvalue_reference<vl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_member_rvalue_reference<cvl>>{});
        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<r>>{});
        CT_ASSERT(!std::is_same<r,  ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<cr>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<vr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cvr>>{});
    }

    {
        using f   = void(foo::*&&)(...);
        using l   = void(foo::*&&)(...) &;
        using r   = void(foo::*&&)(...) &&;
        using c   = void(foo::*&&)(...) const;
        using cl  = void(foo::*&&)(...) const &;
        using cr  = void(foo::*&&)(...) const &&;
        using v   = void(foo::*&&)(...) volatile;
        using vl  = void(foo::*&&)(...) volatile &;
        using vr  = void(foo::*&&)(...) volatile &&;
        using cv  = void(foo::*&&)(...) const volatile;
        using cvl = void(foo::*&&)(...) const volatile &;
        using cvr = void(foo::*&&)(...) const volatile &&;

        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<f>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<c>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<v>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cv>>{});
        CT_ASSERT(std::is_same<l,   ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cl,  ct::add_member_rvalue_reference<cl>>{});
        CT_ASSERT(std::is_same<vl,  ct::add_member_rvalue_reference<vl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_member_rvalue_reference<cvl>>{});
        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<r>>{});
        CT_ASSERT(!std::is_same<r,  ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<cr>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<vr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cvr>>{});
    }
    
    {
        using f   = void(foo::* const)();
        using l   = void(foo::* const)() &;
        using r   = void(foo::* const)() &&;
        using c   = void(foo::* const)() const;
        using cl  = void(foo::* const)() const &;
        using cr  = void(foo::* const)() const &&;
        using v   = void(foo::* const)() volatile;
        using vl  = void(foo::* const)() volatile &;
        using vr  = void(foo::* const)() volatile &&;
        using cv  = void(foo::* const)() const volatile;
        using cvl = void(foo::* const)() const volatile &;
        using cvr = void(foo::* const)() const volatile &&;

        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<f>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<c>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<v>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cv>>{});
        CT_ASSERT(std::is_same<l,   ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cl,  ct::add_member_rvalue_reference<cl>>{});
        CT_ASSERT(std::is_same<vl,  ct::add_member_rvalue_reference<vl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_member_rvalue_reference<cvl>>{});
        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<r>>{});
        CT_ASSERT(!std::is_same<r,  ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<cr>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<vr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cvr>>{});
    }
    
    {
        using f   = void();
        using l   = void() &;
        using r   = void() &&;
        using c   = void() const;
        using cl  = void() const &;
        using cr  = void() const &&;
        using v   = void() volatile;
        using vl  = void() volatile &;
        using vr  = void() volatile &&;
        using cv  = void() const volatile;
        using cvl = void() const volatile &;
        using cvr = void() const volatile &&;

        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<f>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<c>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<v>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cv>>{});
        CT_ASSERT(std::is_same<l,   ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cl,  ct::add_member_rvalue_reference<cl>>{});
        CT_ASSERT(std::is_same<vl,  ct::add_member_rvalue_reference<vl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_member_rvalue_reference<cvl>>{});
        CT_ASSERT(std::is_same<r,   ct::add_member_rvalue_reference<r>>{});
        CT_ASSERT(!std::is_same<r,  ct::add_member_rvalue_reference<l>>{});
        CT_ASSERT(std::is_same<cr,  ct::add_member_rvalue_reference<cr>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_rvalue_reference<vr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_rvalue_reference<cvr>>{});
    }
}

#endif //#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
