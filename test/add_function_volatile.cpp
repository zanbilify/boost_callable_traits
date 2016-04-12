/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/add_function_volatile.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo{};

namespace ct = callable_traits;

int main() {
	
	{
		using f   = int(foo::*)(int);
		using l   = int(foo::*)(int) &;
		using r   = int(foo::*)(int) &&;
		using c   = int(foo::*)(int) const;
		using cl  = int(foo::*)(int) const &;
		using cr  = int(foo::*)(int) const &&;
		using v   = int(foo::*)(int) volatile;
		using vl  = int(foo::*)(int) volatile &;
		using vr  = int(foo::*)(int) volatile &&;
		using cv  = int(foo::*)(int) const volatile;
		using cvl = int(foo::*)(int) const volatile &;
		using cvr = int(foo::*)(int) const volatile &&;

		CT_ASSERT(std::is_same<v,   ct::add_function_volatile<f>>{});
		CT_ASSERT(std::is_same<v,   ct::add_function_volatile<v>>{});
		CT_ASSERT(std::is_same<vr,  ct::add_function_volatile<r>>{});
		CT_ASSERT(std::is_same<vr,  ct::add_function_volatile<vr>>{});
		CT_ASSERT(std::is_same<cv,  ct::add_function_volatile<c>>{});
		CT_ASSERT(std::is_same<cv,  ct::add_function_volatile<cv>>{});
		CT_ASSERT(std::is_same<cvl, ct::add_function_volatile<cl>>{});
		CT_ASSERT(std::is_same<cvl, ct::add_function_volatile<cvl>>{});
		CT_ASSERT(std::is_same<cvr, ct::add_function_volatile<cr>>{});
		CT_ASSERT(std::is_same<cvr, ct::add_function_volatile<cvr>>{});
	}
	
	{
		using f   = foo();
		using l   = foo() &;
		using r   = foo() &&;
		using c   = foo() const;
		using cl  = foo() const &;
		using cr  = foo() const &&;
		using v   = foo() volatile;
		using vl  = foo() volatile &;
		using vr  = foo() volatile &&;
		using cv  = foo() const volatile;
		using cvl = foo() const volatile &;
		using cvr = foo() const volatile &&;

		CT_ASSERT(std::is_same<v,   ct::add_function_volatile<f>>{});
		CT_ASSERT(std::is_same<v,   ct::add_function_volatile<v>>{});
		CT_ASSERT(std::is_same<vr,  ct::add_function_volatile<r>>{});
		CT_ASSERT(std::is_same<vr,  ct::add_function_volatile<vr>>{});
		CT_ASSERT(std::is_same<cv,  ct::add_function_volatile<c>>{});
		CT_ASSERT(std::is_same<cv,  ct::add_function_volatile<cv>>{});
		CT_ASSERT(std::is_same<cvl, ct::add_function_volatile<cl>>{});
		CT_ASSERT(std::is_same<cvl, ct::add_function_volatile<cvl>>{});
		CT_ASSERT(std::is_same<cvr, ct::add_function_volatile<cr>>{});
		CT_ASSERT(std::is_same<cvr, ct::add_function_volatile<cvr>>{});
	}
}
