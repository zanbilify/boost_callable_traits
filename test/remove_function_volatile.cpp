/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/remove_function_volatile.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo{};

namespace ct = callable_traits;

int main() {
	
	{
		using f   = char(foo::*)(foo*, int);
		using l   = char(foo::*)(foo*, int) &;
		using r   = char(foo::*)(foo*, int) &&;
		using c   = char(foo::*)(foo*, int) const;
		using cl  = char(foo::*)(foo*, int) const &;
		using cr  = char(foo::*)(foo*, int) const &&;
		using v   = char(foo::*)(foo*, int) volatile;
		using vl  = char(foo::*)(foo*, int) volatile &;
		using vr  = char(foo::*)(foo*, int) volatile &&;
		using cv  = char(foo::*)(foo*, int) const volatile;
		using cvl = char(foo::*)(foo*, int) const volatile &;
		using cvr = char(foo::*)(foo*, int) const volatile &&;

		CT_ASSERT(std::is_same<f,   ct::remove_function_volatile<f>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_function_volatile<vl>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_function_volatile<l>>{});
		CT_ASSERT(std::is_same<f,   ct::remove_function_volatile<v>>{});
		CT_ASSERT(std::is_same<r,  ct::remove_function_volatile<r>>{});
		CT_ASSERT(std::is_same<r,  ct::remove_function_volatile<vr>>{});
		CT_ASSERT(std::is_same<c,  ct::remove_function_volatile<c>>{});
		CT_ASSERT(std::is_same<c,  ct::remove_function_volatile<cv>>{});
		CT_ASSERT(std::is_same<cl, ct::remove_function_volatile<cl>>{});
		CT_ASSERT(std::is_same<cl, ct::remove_function_volatile<cvl>>{});
		CT_ASSERT(std::is_same<cr, ct::remove_function_volatile<cr>>{});
		CT_ASSERT(std::is_same<cr, ct::remove_function_volatile<cvr>>{});
	}
	
	{
		using f   = foo&&();
		using l   = foo&&() &;
		using r   = foo&&() &&;
		using c   = foo&&() const;
		using cl  = foo&&() const &;
		using cr  = foo&&() const &&;
		using v   = foo&&() volatile;
		using vl  = foo&&() volatile &;
		using vr  = foo&&() volatile &&;
		using cv  = foo&&() const volatile;
		using cvl = foo&&() const volatile &;
		using cvr = foo&&() const volatile &&;

		CT_ASSERT(std::is_same<f,  ct::remove_function_volatile<f>>{});
		CT_ASSERT(std::is_same<f,  ct::remove_function_volatile<v>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_function_volatile<vl>>{});
        CT_ASSERT(std::is_same<l,   ct::remove_function_volatile<l>>{});
		CT_ASSERT(std::is_same<r,  ct::remove_function_volatile<r>>{});
		CT_ASSERT(std::is_same<r,  ct::remove_function_volatile<vr>>{});
		CT_ASSERT(std::is_same<c,  ct::remove_function_volatile<c>>{});
		CT_ASSERT(std::is_same<c,  ct::remove_function_volatile<cv>>{});
		CT_ASSERT(std::is_same<cl, ct::remove_function_volatile<cl>>{});
		CT_ASSERT(std::is_same<cl, ct::remove_function_volatile<cvl>>{});
		CT_ASSERT(std::is_same<cr, ct::remove_function_volatile<cr>>{});
		CT_ASSERT(std::is_same<cr, ct::remove_function_volatile<cvr>>{});
	}
}
