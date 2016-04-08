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

using pmf = void(foo::*)();
using pmf_l = void(foo::*)() &;
using pmf_r = void(foo::*)() &&;
using pmf_c = void(foo::*)() const;
using pmf_cl = void(foo::*)() const &;
using pmf_cr = void(foo::*)() const &&;
using pmf_v = void(foo::*)() volatile;
using pmf_vl = void(foo::*)() volatile &;
using pmf_vr = void(foo::*)() volatile &&;
using pmf_cv = void(foo::*)() const volatile;
using pmf_cvl = void(foo::*)() const volatile &;
using pmf_cvr = void(foo::*)() const volatile &&;

CT_ASSERT(std::is_same<pmf_l,   ct::add_function_lvalue<pmf>>{});
CT_ASSERT(std::is_same<pmf_r,   ct::add_function_rvalue<pmf>>{});

CT_ASSERT(std::is_same<pmf_c,   ct::add_function_const<pmf>>{});
CT_ASSERT(std::is_same<pmf_cl,  ct::add_function_const<pmf_l>>{});
CT_ASSERT(std::is_same<pmf_cl,  ct::add_function_lvalue<pmf_c>>{});
CT_ASSERT(std::is_same<pmf_cr,  ct::add_function_const<pmf_r>>{});
CT_ASSERT(std::is_same<pmf_cr,  ct::add_function_rvalue<pmf_c>>{});

CT_ASSERT(std::is_same<pmf_v,   ct::add_function_volatile<pmf>>{});
CT_ASSERT(std::is_same<pmf_vl,  ct::add_function_lvalue<pmf_v>>{});
CT_ASSERT(std::is_same<pmf_vl,  ct::add_function_lvalue<pmf_v>>{});
CT_ASSERT(std::is_same<pmf_vr,  ct::add_function_volatile<pmf_r>>{});
CT_ASSERT(std::is_same<pmf_vr,  ct::add_function_rvalue<pmf_v>>{});

CT_ASSERT(std::is_same<pmf_cv,  ct::add_function_cv<pmf>>{});
CT_ASSERT(std::is_same<pmf_cv,  ct::add_function_volatile<pmf_c>>{});
CT_ASSERT(std::is_same<pmf_cv,  ct::add_function_const<pmf_v>>{});
CT_ASSERT(std::is_same<pmf_cvl, ct::add_function_cv<pmf_l>>{});
CT_ASSERT(std::is_same<pmf_cvl, ct::add_function_volatile<pmf_cl>>{});
CT_ASSERT(std::is_same<pmf_cvl, ct::add_function_const<pmf_vl>>{});
CT_ASSERT(std::is_same<pmf_cvl, ct::add_function_lvalue<pmf_cv>>{});
CT_ASSERT(std::is_same<pmf_cvr, ct::add_function_cv<pmf_r>>{});
CT_ASSERT(std::is_same<pmf_cvr, ct::add_function_volatile<pmf_cr>>{});
CT_ASSERT(std::is_same<pmf_cvr, ct::add_function_const<pmf_vr>>{});
CT_ASSERT(std::is_same<pmf_cvr, ct::add_function_rvalue<pmf_cv>>{});

CT_ASSERT(std::is_same<pmf,     ct::remove_function_volatile<pmf_v>>{});
CT_ASSERT(std::is_same<pmf,     ct::remove_function_const<pmf_c>>{});
CT_ASSERT(std::is_same<pmf,     ct::remove_function_reference<pmf_l>>{});
CT_ASSERT(std::is_same<pmf,     ct::remove_function_reference<pmf_r>>{});
CT_ASSERT(std::is_same<pmf,     ct::remove_function_cv<pmf_cv>>{});

CT_ASSERT(std::is_same<pmf_l,   ct::remove_function_volatile<pmf_vl>>{});
CT_ASSERT(std::is_same<pmf_l,   ct::remove_function_const<pmf_cl>>{});
CT_ASSERT(std::is_same<pmf_l,   ct::remove_function_cv<pmf_cvl>>{});

CT_ASSERT(std::is_same<pmf_r,   ct::remove_function_volatile<pmf_vr>>{});
CT_ASSERT(std::is_same<pmf_r,   ct::remove_function_const<pmf_cr>>{});
CT_ASSERT(std::is_same<pmf_r,   ct::remove_function_cv<pmf_cvr>>{});

CT_ASSERT(std::is_same<pmf_c,   ct::remove_function_volatile<pmf_cv>>{});
CT_ASSERT(std::is_same<pmf_c,   ct::remove_function_reference<pmf_cl>>{});
CT_ASSERT(std::is_same<pmf_c,   ct::remove_function_reference<pmf_cr>>{});


CT_ASSERT(std::is_same<pmf_v,   ct::remove_function_const<pmf_cv>>{});
CT_ASSERT(std::is_same<pmf_v,   ct::remove_function_reference<pmf_vl>>{});
CT_ASSERT(std::is_same<pmf_v,   ct::remove_function_reference<pmf_vr>>{});

CT_ASSERT(std::is_same<pmf_cv,  ct::remove_function_reference<pmf_cvl>>{});
CT_ASSERT(std::is_same<pmf_cv,  ct::remove_function_reference<pmf_cvr>>{});

CT_ASSERT(!ct::is_const_qualified<pmf>());
CT_ASSERT(!ct::is_const_qualified(pmf{}));
CT_ASSERT(!ct::is_const_qualified<pmf_l>());
CT_ASSERT(!ct::is_const_qualified(pmf_l{}));
CT_ASSERT(!ct::is_const_qualified<pmf_r>());
CT_ASSERT(!ct::is_const_qualified(pmf_r{}));
CT_ASSERT(ct::is_const_qualified<pmf_c>());
CT_ASSERT(ct::is_const_qualified(pmf_c{}));
CT_ASSERT(ct::is_const_qualified<pmf_cl>());
CT_ASSERT(ct::is_const_qualified(pmf_cl{}));
CT_ASSERT(ct::is_const_qualified<pmf_cr>());
CT_ASSERT(ct::is_const_qualified(pmf_cr{}));
CT_ASSERT(!ct::is_const_qualified<pmf_v>());
CT_ASSERT(!ct::is_const_qualified(pmf_v{}));
CT_ASSERT(!ct::is_const_qualified<pmf_vl>());
CT_ASSERT(!ct::is_const_qualified(pmf_vl{}));
CT_ASSERT(!ct::is_const_qualified<pmf_vr>());
CT_ASSERT(!ct::is_const_qualified(pmf_vr{}));
CT_ASSERT(ct::is_const_qualified<pmf_cv>());
CT_ASSERT(ct::is_const_qualified(pmf_cv{}));
CT_ASSERT(ct::is_const_qualified<pmf_cvl>());
CT_ASSERT(ct::is_const_qualified(pmf_cvl{}));
CT_ASSERT(ct::is_const_qualified<pmf_cvr>());
CT_ASSERT(ct::is_const_qualified(pmf_cvr{}));


CT_ASSERT(!ct::is_volatile_qualified<pmf>());
CT_ASSERT(!ct::is_volatile_qualified(pmf{}));
CT_ASSERT(!ct::is_volatile_qualified<pmf_l>());
CT_ASSERT(!ct::is_volatile_qualified(pmf_l{}));
CT_ASSERT(!ct::is_volatile_qualified<pmf_r>());
CT_ASSERT(!ct::is_volatile_qualified(pmf_r{}));
CT_ASSERT(!ct::is_volatile_qualified<pmf_c>());
CT_ASSERT(!ct::is_volatile_qualified(pmf_c{}));
CT_ASSERT(!ct::is_volatile_qualified<pmf_cl>());
CT_ASSERT(!ct::is_volatile_qualified(pmf_cl{}));
CT_ASSERT(!ct::is_volatile_qualified<pmf_cr>());
CT_ASSERT(!ct::is_volatile_qualified(pmf_cr{}));
CT_ASSERT(ct::is_volatile_qualified<pmf_v>());
CT_ASSERT(ct::is_volatile_qualified(pmf_v{}));
CT_ASSERT(ct::is_volatile_qualified<pmf_vl>());
CT_ASSERT(ct::is_volatile_qualified(pmf_vl{}));
CT_ASSERT(ct::is_volatile_qualified<pmf_vr>());
CT_ASSERT(ct::is_volatile_qualified(pmf_vr{}));
CT_ASSERT(ct::is_volatile_qualified<pmf_cv>());
CT_ASSERT(ct::is_volatile_qualified(pmf_cv{}));
CT_ASSERT(ct::is_volatile_qualified<pmf_cvl>());
CT_ASSERT(ct::is_volatile_qualified(pmf_cvl{}));
CT_ASSERT(ct::is_volatile_qualified<pmf_cvr>());
CT_ASSERT(ct::is_volatile_qualified(pmf_cvr{}));

CT_ASSERT(!ct::is_reference_qualified<pmf>());
CT_ASSERT(!ct::is_reference_qualified(pmf{}));
CT_ASSERT(ct::is_reference_qualified<pmf_l>());
CT_ASSERT(ct::is_reference_qualified(pmf_l{}));
CT_ASSERT(ct::is_reference_qualified<pmf_r>());
CT_ASSERT(ct::is_reference_qualified(pmf_r{}));
CT_ASSERT(!ct::is_reference_qualified<pmf_c>());
CT_ASSERT(!ct::is_reference_qualified(pmf_c{}));
CT_ASSERT(ct::is_reference_qualified<pmf_cl>());
CT_ASSERT(ct::is_reference_qualified(pmf_cl{}));
CT_ASSERT(ct::is_reference_qualified<pmf_cr>());
CT_ASSERT(ct::is_reference_qualified(pmf_cr{}));
CT_ASSERT(!ct::is_reference_qualified<pmf_v>());
CT_ASSERT(!ct::is_reference_qualified(pmf_v{}));
CT_ASSERT(ct::is_reference_qualified<pmf_vl>());
CT_ASSERT(ct::is_reference_qualified(pmf_vl{}));
CT_ASSERT(ct::is_reference_qualified<pmf_vr>());
CT_ASSERT(ct::is_reference_qualified(pmf_vr{}));
CT_ASSERT(!ct::is_reference_qualified<pmf_cv>());
CT_ASSERT(!ct::is_reference_qualified(pmf_cv{}));
CT_ASSERT(ct::is_reference_qualified<pmf_cvl>());
CT_ASSERT(ct::is_reference_qualified(pmf_cvl{}));
CT_ASSERT(ct::is_reference_qualified<pmf_cvr>());
CT_ASSERT(ct::is_reference_qualified(pmf_cvr{}));

CT_ASSERT(!ct::is_lvalue_qualified<pmf>());
CT_ASSERT(!ct::is_lvalue_qualified(pmf{}));
CT_ASSERT(ct::is_lvalue_qualified<pmf_l>());
CT_ASSERT(ct::is_lvalue_qualified(pmf_l{}));
CT_ASSERT(!ct::is_lvalue_qualified<pmf_r>());
CT_ASSERT(!ct::is_lvalue_qualified(pmf_r{}));
CT_ASSERT(!ct::is_lvalue_qualified<pmf_c>());
CT_ASSERT(!ct::is_lvalue_qualified(pmf_c{}));
CT_ASSERT(ct::is_lvalue_qualified<pmf_cl>());
CT_ASSERT(ct::is_lvalue_qualified(pmf_cl{}));
CT_ASSERT(!ct::is_lvalue_qualified<pmf_cr>());
CT_ASSERT(!ct::is_lvalue_qualified(pmf_cr{}));
CT_ASSERT(!ct::is_lvalue_qualified<pmf_v>());
CT_ASSERT(!ct::is_lvalue_qualified(pmf_v{}));
CT_ASSERT(ct::is_lvalue_qualified<pmf_vl>());
CT_ASSERT(ct::is_lvalue_qualified(pmf_vl{}));
CT_ASSERT(!ct::is_lvalue_qualified<pmf_vr>());
CT_ASSERT(!ct::is_lvalue_qualified(pmf_vr{}));
CT_ASSERT(!ct::is_lvalue_qualified<pmf_cv>());
CT_ASSERT(!ct::is_lvalue_qualified(pmf_cv{}));
CT_ASSERT(ct::is_lvalue_qualified<pmf_cvl>());
CT_ASSERT(ct::is_lvalue_qualified(pmf_cvl{}));
CT_ASSERT(!ct::is_lvalue_qualified<pmf_cvr>());
CT_ASSERT(!ct::is_lvalue_qualified(pmf_cvr{}));

CT_ASSERT(!ct::is_rvalue_qualified<pmf>());
CT_ASSERT(!ct::is_rvalue_qualified(pmf{}));
CT_ASSERT(!ct::is_rvalue_qualified<pmf_l>());
CT_ASSERT(!ct::is_rvalue_qualified(pmf_l{}));
CT_ASSERT(ct::is_rvalue_qualified<pmf_r>());
CT_ASSERT(ct::is_rvalue_qualified(pmf_r{}));
CT_ASSERT(!ct::is_rvalue_qualified<pmf_c>());
CT_ASSERT(!ct::is_rvalue_qualified(pmf_c{}));
CT_ASSERT(!ct::is_rvalue_qualified<pmf_cl>());
CT_ASSERT(!ct::is_rvalue_qualified(pmf_cl{}));
CT_ASSERT(ct::is_rvalue_qualified<pmf_cr>());
CT_ASSERT(ct::is_rvalue_qualified(pmf_cr{}));
CT_ASSERT(!ct::is_rvalue_qualified<pmf_v>());
CT_ASSERT(!ct::is_rvalue_qualified(pmf_v{}));
CT_ASSERT(!ct::is_rvalue_qualified<pmf_vl>());
CT_ASSERT(!ct::is_rvalue_qualified(pmf_vl{}));
CT_ASSERT(ct::is_rvalue_qualified<pmf_vr>());
CT_ASSERT(ct::is_rvalue_qualified(pmf_vr{}));
CT_ASSERT(!ct::is_rvalue_qualified<pmf_cv>());
CT_ASSERT(!ct::is_rvalue_qualified(pmf_cv{}));
CT_ASSERT(!ct::is_rvalue_qualified<pmf_cvl>());
CT_ASSERT(!ct::is_rvalue_qualified(pmf_cvl{}));
CT_ASSERT(ct::is_rvalue_qualified<pmf_cvr>());
CT_ASSERT(ct::is_rvalue_qualified(pmf_cvr{}));

int main() { return 0; }
