/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/remove_member_volatile.hpp>

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

        CT_ASSERT(std::is_same<f,  ct::remove_member_volatile<f>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_member_volatile<vl>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_member_volatile<l>>{});
        CT_ASSERT(std::is_same<f,  ct::remove_member_volatile<v>>{});
		CT_ASSERT(std::is_same<r,  ct::remove_member_volatile<r>>{});
		CT_ASSERT(std::is_same<r,  ct::remove_member_volatile<vr>>{});
		CT_ASSERT(std::is_same<c,  ct::remove_member_volatile<c>>{});
		CT_ASSERT(std::is_same<c,  ct::remove_member_volatile<cv>>{});
		CT_ASSERT(std::is_same<cl, ct::remove_member_volatile<cl>>{});
		CT_ASSERT(std::is_same<cl, ct::remove_member_volatile<cvl>>{});
		CT_ASSERT(std::is_same<cr, ct::remove_member_volatile<cr>>{});
		CT_ASSERT(std::is_same<cr, ct::remove_member_volatile<cvr>>{});
	}
	
#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

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

		CT_ASSERT(std::is_same<f,  ct::remove_member_volatile<f>>{});
		CT_ASSERT(std::is_same<f,  ct::remove_member_volatile<v>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_member_volatile<vl>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_member_volatile<l>>{});
		CT_ASSERT(std::is_same<r,  ct::remove_member_volatile<r>>{});
		CT_ASSERT(std::is_same<r,  ct::remove_member_volatile<vr>>{});
		CT_ASSERT(std::is_same<c,  ct::remove_member_volatile<c>>{});
		CT_ASSERT(std::is_same<c,  ct::remove_member_volatile<cv>>{});
		CT_ASSERT(std::is_same<cl, ct::remove_member_volatile<cl>>{});
		CT_ASSERT(std::is_same<cl, ct::remove_member_volatile<cvl>>{});
		CT_ASSERT(std::is_same<cr, ct::remove_member_volatile<cr>>{});
		CT_ASSERT(std::is_same<cr, ct::remove_member_volatile<cvr>>{});
	}

#endif //#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

}
