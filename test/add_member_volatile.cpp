/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/add_member_volatile.hpp>

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

struct foo{};

namespace ct = callable_traits;

int main() {
    
    {
        using f   = int(foo::*)(int);
        using l   = int(foo::*)(int) LREF;
        using r   = int(foo::*)(int) RREF;
        using c   = int(foo::*)(int) const;
        using cl  = int(foo::*)(int) const LREF;
        using cr  = int(foo::*)(int) const RREF;
        using v   = int(foo::*)(int) volatile;
        using vl  = int(foo::*)(int) volatile LREF;
        using vr  = int(foo::*)(int) volatile RREF;
        using cv  = int(foo::*)(int) const volatile;
        using cvl = int(foo::*)(int) const volatile LREF;
        using cvr = int(foo::*)(int) const volatile RREF;

        CT_ASSERT(std::is_same<v,   ct::add_member_volatile_t<f>>{});
        CT_ASSERT(std::is_same<v,   ct::add_member_volatile_t<v>>{});
        CT_ASSERT(std::is_same<vl,   ct::add_member_volatile_t<l>>{});
        CT_ASSERT(std::is_same<vl,   ct::add_member_volatile_t<vl>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_volatile_t<r>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_volatile_t<vr>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_member_volatile_t<c>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_member_volatile_t<cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_member_volatile_t<cl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_member_volatile_t<cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_volatile_t<cr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_volatile_t<cvr>>{});
    }
    
#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

    {
        using f   = foo();
        using l   = foo() LREF;
        using r   = foo() RREF;
        using c   = foo() const;
        using cl  = foo() const LREF;
        using cr  = foo() const RREF;
        using v   = foo() volatile;
        using vl  = foo() volatile LREF;
        using vr  = foo() volatile RREF;
        using cv  = foo() const volatile;
        using cvl = foo() const volatile LREF;
        using cvr = foo() const volatile RREF;

        CT_ASSERT(std::is_same<v,   ct::add_member_volatile_t<f>>{});
        CT_ASSERT(std::is_same<v,   ct::add_member_volatile_t<v>>{});
        CT_ASSERT(std::is_same<vl,   ct::add_member_volatile_t<l>>{});
        CT_ASSERT(std::is_same<vl,   ct::add_member_volatile_t<vl>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_volatile_t<r>>{});
        CT_ASSERT(std::is_same<vr,  ct::add_member_volatile_t<vr>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_member_volatile_t<c>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_member_volatile_t<cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_member_volatile_t<cl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_member_volatile_t<cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_volatile_t<cr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_member_volatile_t<cvr>>{});
    }

#endif
}
