/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/callable_traits.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo{};

namespace ct = callable_traits;

using f = void(foo::*)();
using l = void(foo::*)() &;
using r = void(foo::*)() &&;
using c = void(foo::*)() const;
using cl = void(foo::*)() const &;
using cr = void(foo::*)() const &&;
using v = void(foo::*)() volatile;
using vl = void(foo::*)() volatile &;
using vr = void(foo::*)() volatile &&;
using cv = void(foo::*)() const volatile;
using cvl = void(foo::*)() const volatile &;
using cvr = void(foo::*)() const volatile &&;

CT_ASSERT(std::is_same<l,   ct::add_function_lvalue<f>>{});
CT_ASSERT(std::is_same<r,   ct::add_function_rvalue<f>>{});

CT_ASSERT(std::is_same<c,   ct::add_function_const<f>>{});
CT_ASSERT(std::is_same<cl,  ct::add_function_const<l>>{});
CT_ASSERT(std::is_same<cl,  ct::add_function_lvalue<c>>{});
CT_ASSERT(std::is_same<cr,  ct::add_function_const<r>>{});
CT_ASSERT(std::is_same<cr,  ct::add_function_rvalue<c>>{});

CT_ASSERT(std::is_same<v,   ct::add_function_volatile<f>>{});
CT_ASSERT(std::is_same<vl,  ct::add_function_lvalue<v>>{});
CT_ASSERT(std::is_same<vl,  ct::add_function_lvalue<v>>{});
CT_ASSERT(std::is_same<vr,  ct::add_function_volatile<r>>{});
CT_ASSERT(std::is_same<vr,  ct::add_function_rvalue<v>>{});

CT_ASSERT(std::is_same<cv,  ct::add_function_cv<f>>{});
CT_ASSERT(std::is_same<cv,  ct::add_function_volatile<c>>{});
CT_ASSERT(std::is_same<cv,  ct::add_function_const<v>>{});
CT_ASSERT(std::is_same<cvl, ct::add_function_cv<l>>{});
CT_ASSERT(std::is_same<cvl, ct::add_function_volatile<cl>>{});
CT_ASSERT(std::is_same<cvl, ct::add_function_const<vl>>{});
CT_ASSERT(std::is_same<cvl, ct::add_function_lvalue<cv>>{});
CT_ASSERT(std::is_same<cvr, ct::add_function_cv<r>>{});
CT_ASSERT(std::is_same<cvr, ct::add_function_volatile<cr>>{});
CT_ASSERT(std::is_same<cvr, ct::add_function_const<vr>>{});
CT_ASSERT(std::is_same<cvr, ct::add_function_rvalue<cv>>{});

CT_ASSERT(std::is_same<f,     ct::remove_function_volatile<v>>{});
CT_ASSERT(std::is_same<f,     ct::remove_function_const<c>>{});
CT_ASSERT(std::is_same<f,     ct::remove_function_reference<l>>{});
CT_ASSERT(std::is_same<f,     ct::remove_function_reference<r>>{});
CT_ASSERT(std::is_same<f,     ct::remove_function_cv<cv>>{});

CT_ASSERT(std::is_same<l,   ct::remove_function_volatile<vl>>{});
CT_ASSERT(std::is_same<l,   ct::remove_function_const<cl>>{});
CT_ASSERT(std::is_same<l,   ct::remove_function_cv<cvl>>{});
CT_ASSERT(std::is_same<l,   ct::add_function_rvalue<l>>{});
CT_ASSERT(std::is_same<l,   ct::add_function_lvalue<l>>{});

CT_ASSERT(std::is_same<r,   ct::remove_function_volatile<vr>>{});
CT_ASSERT(std::is_same<r,   ct::remove_function_const<cr>>{});
CT_ASSERT(std::is_same<r,   ct::remove_function_cv<cvr>>{});

CT_ASSERT(std::is_same<c,   ct::remove_function_volatile<cv>>{});
CT_ASSERT(std::is_same<c,   ct::remove_function_reference<cl>>{});
CT_ASSERT(std::is_same<c,   ct::remove_function_reference<cr>>{});


CT_ASSERT(std::is_same<v,   ct::remove_function_const<cv>>{});
CT_ASSERT(std::is_same<v,   ct::remove_function_reference<vl>>{});
CT_ASSERT(std::is_same<v,   ct::remove_function_reference<vr>>{});

CT_ASSERT(std::is_same<cv,  ct::remove_function_reference<cvl>>{});
CT_ASSERT(std::is_same<cv,  ct::remove_function_reference<cvr>>{});

//reference collapsing from &
CT_ASSERT(std::is_same<cl,   ct::add_function_rvalue<cl>>{});
CT_ASSERT(std::is_same<cl,   ct::add_function_lvalue<cl>>{});
CT_ASSERT(std::is_same<vl,   ct::add_function_rvalue<vl>>{});
CT_ASSERT(std::is_same<vl,   ct::add_function_lvalue<vl>>{});
CT_ASSERT(std::is_same<cvl,   ct::add_function_rvalue<cvl>>{});
CT_ASSERT(std::is_same<cvl,   ct::add_function_lvalue<cvl>>{});

//reference collapsing from &&
CT_ASSERT(std::is_same<r,   ct::add_function_rvalue<r>>{});
CT_ASSERT(!std::is_same<r,   ct::add_function_rvalue<l>>{});
CT_ASSERT(!std::is_same<r,   ct::add_function_lvalue<r>>{});
CT_ASSERT(std::is_same<cr,   ct::add_function_rvalue<cr>>{});
CT_ASSERT(!std::is_same<cr,   ct::add_function_lvalue<cr>>{});
CT_ASSERT(std::is_same<vr,   ct::add_function_rvalue<vr>>{});
CT_ASSERT(!std::is_same<vr,   ct::add_function_lvalue<vr>>{});
CT_ASSERT(std::is_same<cvr,   ct::add_function_rvalue<cvr>>{});
CT_ASSERT(!std::is_same<cvr,   ct::add_function_lvalue<cvr>>{});

CT_ASSERT(!ct::is_const_qualified<f>());
CT_ASSERT(!ct::is_const_qualified(f{}));
CT_ASSERT(!ct::is_const_qualified<l>());
CT_ASSERT(!ct::is_const_qualified(l{}));
CT_ASSERT(!ct::is_const_qualified<r>());
CT_ASSERT(!ct::is_const_qualified(r{}));
CT_ASSERT(ct::is_const_qualified<c>());
CT_ASSERT(ct::is_const_qualified(c{}));
CT_ASSERT(ct::is_const_qualified<cl>());
CT_ASSERT(ct::is_const_qualified(cl{}));
CT_ASSERT(ct::is_const_qualified<cr>());
CT_ASSERT(ct::is_const_qualified(cr{}));
CT_ASSERT(!ct::is_const_qualified<v>());
CT_ASSERT(!ct::is_const_qualified(v{}));
CT_ASSERT(!ct::is_const_qualified<vl>());
CT_ASSERT(!ct::is_const_qualified(vl{}));
CT_ASSERT(!ct::is_const_qualified<vr>());
CT_ASSERT(!ct::is_const_qualified(vr{}));
CT_ASSERT(ct::is_const_qualified<cv>());
CT_ASSERT(ct::is_const_qualified(cv{}));
CT_ASSERT(ct::is_const_qualified<cvl>());
CT_ASSERT(ct::is_const_qualified(cvl{}));
CT_ASSERT(ct::is_const_qualified<cvr>());
CT_ASSERT(ct::is_const_qualified(cvr{}));


CT_ASSERT(!ct::is_volatile_qualified<f>());
CT_ASSERT(!ct::is_volatile_qualified(f{}));
CT_ASSERT(!ct::is_volatile_qualified<l>());
CT_ASSERT(!ct::is_volatile_qualified(l{}));
CT_ASSERT(!ct::is_volatile_qualified<r>());
CT_ASSERT(!ct::is_volatile_qualified(r{}));
CT_ASSERT(!ct::is_volatile_qualified<c>());
CT_ASSERT(!ct::is_volatile_qualified(c{}));
CT_ASSERT(!ct::is_volatile_qualified<cl>());
CT_ASSERT(!ct::is_volatile_qualified(cl{}));
CT_ASSERT(!ct::is_volatile_qualified<cr>());
CT_ASSERT(!ct::is_volatile_qualified(cr{}));
CT_ASSERT(ct::is_volatile_qualified<v>());
CT_ASSERT(ct::is_volatile_qualified(v{}));
CT_ASSERT(ct::is_volatile_qualified<vl>());
CT_ASSERT(ct::is_volatile_qualified(vl{}));
CT_ASSERT(ct::is_volatile_qualified<vr>());
CT_ASSERT(ct::is_volatile_qualified(vr{}));
CT_ASSERT(ct::is_volatile_qualified<cv>());
CT_ASSERT(ct::is_volatile_qualified(cv{}));
CT_ASSERT(ct::is_volatile_qualified<cvl>());
CT_ASSERT(ct::is_volatile_qualified(cvl{}));
CT_ASSERT(ct::is_volatile_qualified<cvr>());
CT_ASSERT(ct::is_volatile_qualified(cvr{}));

CT_ASSERT(!ct::is_reference_qualified<f>());
CT_ASSERT(!ct::is_reference_qualified(f{}));
CT_ASSERT(ct::is_reference_qualified<l>());
CT_ASSERT(ct::is_reference_qualified(l{}));
CT_ASSERT(ct::is_reference_qualified<r>());
CT_ASSERT(ct::is_reference_qualified(r{}));
CT_ASSERT(!ct::is_reference_qualified<c>());
CT_ASSERT(!ct::is_reference_qualified(c{}));
CT_ASSERT(ct::is_reference_qualified<cl>());
CT_ASSERT(ct::is_reference_qualified(cl{}));
CT_ASSERT(ct::is_reference_qualified<cr>());
CT_ASSERT(ct::is_reference_qualified(cr{}));
CT_ASSERT(!ct::is_reference_qualified<v>());
CT_ASSERT(!ct::is_reference_qualified(v{}));
CT_ASSERT(ct::is_reference_qualified<vl>());
CT_ASSERT(ct::is_reference_qualified(vl{}));
CT_ASSERT(ct::is_reference_qualified<vr>());
CT_ASSERT(ct::is_reference_qualified(vr{}));
CT_ASSERT(!ct::is_reference_qualified<cv>());
CT_ASSERT(!ct::is_reference_qualified(cv{}));
CT_ASSERT(ct::is_reference_qualified<cvl>());
CT_ASSERT(ct::is_reference_qualified(cvl{}));
CT_ASSERT(ct::is_reference_qualified<cvr>());
CT_ASSERT(ct::is_reference_qualified(cvr{}));

CT_ASSERT(!ct::is_lvalue_qualified<f>());
CT_ASSERT(!ct::is_lvalue_qualified(f{}));
CT_ASSERT(ct::is_lvalue_qualified<l>());
CT_ASSERT(ct::is_lvalue_qualified(l{}));
CT_ASSERT(!ct::is_lvalue_qualified<r>());
CT_ASSERT(!ct::is_lvalue_qualified(r{}));
CT_ASSERT(!ct::is_lvalue_qualified<c>());
CT_ASSERT(!ct::is_lvalue_qualified(c{}));
CT_ASSERT(ct::is_lvalue_qualified<cl>());
CT_ASSERT(ct::is_lvalue_qualified(cl{}));
CT_ASSERT(!ct::is_lvalue_qualified<cr>());
CT_ASSERT(!ct::is_lvalue_qualified(cr{}));
CT_ASSERT(!ct::is_lvalue_qualified<v>());
CT_ASSERT(!ct::is_lvalue_qualified(v{}));
CT_ASSERT(ct::is_lvalue_qualified<vl>());
CT_ASSERT(ct::is_lvalue_qualified(vl{}));
CT_ASSERT(!ct::is_lvalue_qualified<vr>());
CT_ASSERT(!ct::is_lvalue_qualified(vr{}));
CT_ASSERT(!ct::is_lvalue_qualified<cv>());
CT_ASSERT(!ct::is_lvalue_qualified(cv{}));
CT_ASSERT(ct::is_lvalue_qualified<cvl>());
CT_ASSERT(ct::is_lvalue_qualified(cvl{}));
CT_ASSERT(!ct::is_lvalue_qualified<cvr>());
CT_ASSERT(!ct::is_lvalue_qualified(cvr{}));

CT_ASSERT(!ct::is_rvalue_qualified<f>());
CT_ASSERT(!ct::is_rvalue_qualified(f{}));
CT_ASSERT(!ct::is_rvalue_qualified<l>());
CT_ASSERT(!ct::is_rvalue_qualified(l{}));
CT_ASSERT(ct::is_rvalue_qualified<r>());
CT_ASSERT(ct::is_rvalue_qualified(r{}));
CT_ASSERT(!ct::is_rvalue_qualified<c>());
CT_ASSERT(!ct::is_rvalue_qualified(c{}));
CT_ASSERT(!ct::is_rvalue_qualified<cl>());
CT_ASSERT(!ct::is_rvalue_qualified(cl{}));
CT_ASSERT(ct::is_rvalue_qualified<cr>());
CT_ASSERT(ct::is_rvalue_qualified(cr{}));
CT_ASSERT(!ct::is_rvalue_qualified<v>());
CT_ASSERT(!ct::is_rvalue_qualified(v{}));
CT_ASSERT(!ct::is_rvalue_qualified<vl>());
CT_ASSERT(!ct::is_rvalue_qualified(vl{}));
CT_ASSERT(ct::is_rvalue_qualified<vr>());
CT_ASSERT(ct::is_rvalue_qualified(vr{}));
CT_ASSERT(!ct::is_rvalue_qualified<cv>());
CT_ASSERT(!ct::is_rvalue_qualified(cv{}));
CT_ASSERT(!ct::is_rvalue_qualified<cvl>());
CT_ASSERT(!ct::is_rvalue_qualified(cvl{}));
CT_ASSERT(ct::is_rvalue_qualified<cvr>());
CT_ASSERT(ct::is_rvalue_qualified(cvr{}));

int main() { return 0; }
