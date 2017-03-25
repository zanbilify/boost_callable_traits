/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <boost/callable_traits/remove_member_volatile.hpp>
#include "test.hpp"

struct foo{};

int main() {
    
    {
        using f   = char(foo::*)(foo*, int);
        using l   = char(foo::*)(foo*, int) LREF;
        using r   = char(foo::*)(foo*, int) RREF;
        using c   = char(foo::*)(foo*, int) const;
        using cl  = char(foo::*)(foo*, int) const LREF;
        using cr  = char(foo::*)(foo*, int) const RREF;
        using v   = char(foo::*)(foo*, int) volatile;
        using vl  = char(foo::*)(foo*, int) volatile LREF;
        using vr  = char(foo::*)(foo*, int) volatile RREF;
        using cv  = char(foo::*)(foo*, int) const volatile;
        using cvl = char(foo::*)(foo*, int) const volatile LREF;
        using cvr = char(foo::*)(foo*, int) const volatile RREF;

        CT_ASSERT(std::is_same<f,   remove_member_volatile_t<f>>{});
        CT_ASSERT(std::is_same<l,   remove_member_volatile_t<vl>>{});
        CT_ASSERT(std::is_same<l,   remove_member_volatile_t<l>>{});
        CT_ASSERT(std::is_same<f,   remove_member_volatile_t<v>>{});
        CT_ASSERT(std::is_same<r,   remove_member_volatile_t<r>>{});
        CT_ASSERT(std::is_same<r,   remove_member_volatile_t<vr>>{});
        CT_ASSERT(std::is_same<c,   remove_member_volatile_t<c>>{});
        CT_ASSERT(std::is_same<c,   remove_member_volatile_t<cv>>{});
        CT_ASSERT(std::is_same<cl,  remove_member_volatile_t<cl>>{});
        CT_ASSERT(std::is_same<cl,  remove_member_volatile_t<cvl>>{});
        CT_ASSERT(std::is_same<cr,  remove_member_volatile_t<cr>>{});
        CT_ASSERT(std::is_same<cr,  remove_member_volatile_t<cvr>>{});
    }
    
#ifndef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    {
        using f   = foo&&();
        using l   = foo&&() LREF;
        using r   = foo&&() RREF;
        using c   = foo&&() const;
        using cl  = foo&&() const LREF;
        using cr  = foo&&() const RREF;
        using v   = foo&&() volatile;
        using vl  = foo&&() volatile LREF;
        using vr  = foo&&() volatile RREF;
        using cv  = foo&&() const volatile;
        using cvl = foo&&() const volatile LREF;
        using cvr = foo&&() const volatile RREF;

        CT_ASSERT(std::is_same<f,   remove_member_volatile_t<f>>{});
        CT_ASSERT(std::is_same<f,   remove_member_volatile_t<v>>{});
        CT_ASSERT(std::is_same<l,   remove_member_volatile_t<vl>>{});
        CT_ASSERT(std::is_same<l,   remove_member_volatile_t<l>>{});
        CT_ASSERT(std::is_same<r,   remove_member_volatile_t<r>>{});
        CT_ASSERT(std::is_same<r,   remove_member_volatile_t<vr>>{});
        CT_ASSERT(std::is_same<c,   remove_member_volatile_t<c>>{});
        CT_ASSERT(std::is_same<c,   remove_member_volatile_t<cv>>{});
        CT_ASSERT(std::is_same<cl,  remove_member_volatile_t<cl>>{});
        CT_ASSERT(std::is_same<cl,  remove_member_volatile_t<cvl>>{});
        CT_ASSERT(std::is_same<cr,  remove_member_volatile_t<cr>>{});
        CT_ASSERT(std::is_same<cr,  remove_member_volatile_t<cvr>>{});
    }

#endif //#ifndef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

}
