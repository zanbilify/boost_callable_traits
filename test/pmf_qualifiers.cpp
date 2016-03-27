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

CT_ASSERT(std::is_same<pmf_l,   ct::add_lvalue_qualifier<pmf>>{});
CT_ASSERT(std::is_same<pmf_r,   ct::add_rvalue_qualifier<pmf>>{});

CT_ASSERT(std::is_same<pmf_c,   ct::add_const_qualifier<pmf>>{});
CT_ASSERT(std::is_same<pmf_cl,  ct::add_const_qualifier<pmf_l>>{});
CT_ASSERT(std::is_same<pmf_cl,  ct::add_lvalue_qualifier<pmf_c>>{});
CT_ASSERT(std::is_same<pmf_cr,  ct::add_const_qualifier<pmf_r>>{});
CT_ASSERT(std::is_same<pmf_cr,  ct::add_rvalue_qualifier<pmf_c>>{});

CT_ASSERT(std::is_same<pmf_v,   ct::add_volatile_qualifier<pmf>>{});
CT_ASSERT(std::is_same<pmf_vl,  ct::add_lvalue_qualifier<pmf_v>>{});
CT_ASSERT(std::is_same<pmf_vl,  ct::add_lvalue_qualifier<pmf_v>>{});
CT_ASSERT(std::is_same<pmf_vr,  ct::add_volatile_qualifier<pmf_r>>{});
CT_ASSERT(std::is_same<pmf_vr,  ct::add_rvalue_qualifier<pmf_v>>{});

CT_ASSERT(std::is_same<pmf_cv,  ct::add_cv_qualifiers<pmf>>{});
CT_ASSERT(std::is_same<pmf_cv,  ct::add_volatile_qualifier<pmf_c>>{});
CT_ASSERT(std::is_same<pmf_cv,  ct::add_const_qualifier<pmf_v>>{});
CT_ASSERT(std::is_same<pmf_cvl, ct::add_cv_qualifiers<pmf_l>>{});
CT_ASSERT(std::is_same<pmf_cvl, ct::add_volatile_qualifier<pmf_cl>>{});
CT_ASSERT(std::is_same<pmf_cvl, ct::add_const_qualifier<pmf_vl>>{});
CT_ASSERT(std::is_same<pmf_cvl, ct::add_lvalue_qualifier<pmf_cv>>{});
CT_ASSERT(std::is_same<pmf_cvr, ct::add_cv_qualifiers<pmf_r>>{});
CT_ASSERT(std::is_same<pmf_cvr, ct::add_volatile_qualifier<pmf_cr>>{});
CT_ASSERT(std::is_same<pmf_cvr, ct::add_const_qualifier<pmf_vr>>{});
CT_ASSERT(std::is_same<pmf_cvr, ct::add_rvalue_qualifier<pmf_cv>>{});

CT_ASSERT(std::is_same<pmf,     ct::remove_volatile_qualifier<pmf_v>>{});
CT_ASSERT(std::is_same<pmf,     ct::remove_const_qualifier<pmf_c>>{});
CT_ASSERT(std::is_same<pmf,     ct::remove_reference_qualifier<pmf_l>>{});
CT_ASSERT(std::is_same<pmf,     ct::remove_reference_qualifier<pmf_r>>{});
CT_ASSERT(std::is_same<pmf,     ct::remove_cv_qualifiers<pmf_cv>>{});

CT_ASSERT(std::is_same<pmf_l,   ct::remove_volatile_qualifier<pmf_vl>>{});
CT_ASSERT(std::is_same<pmf_l,   ct::remove_const_qualifier<pmf_cl>>{});
CT_ASSERT(std::is_same<pmf_l,   ct::remove_cv_qualifiers<pmf_cvl>>{});

CT_ASSERT(std::is_same<pmf_r,   ct::remove_volatile_qualifier<pmf_vr>>{});
CT_ASSERT(std::is_same<pmf_r,   ct::remove_const_qualifier<pmf_cr>>{});
CT_ASSERT(std::is_same<pmf_r,   ct::remove_cv_qualifiers<pmf_cvr>>{});

CT_ASSERT(std::is_same<pmf_c,   ct::remove_volatile_qualifier<pmf_cv>>{});
CT_ASSERT(std::is_same<pmf_c,   ct::remove_reference_qualifier<pmf_cl>>{});
CT_ASSERT(std::is_same<pmf_c,   ct::remove_reference_qualifier<pmf_cr>>{});


CT_ASSERT(std::is_same<pmf_v,   ct::remove_const_qualifier<pmf_cv>>{});
CT_ASSERT(std::is_same<pmf_v,   ct::remove_reference_qualifier<pmf_vl>>{});
CT_ASSERT(std::is_same<pmf_v,   ct::remove_reference_qualifier<pmf_vr>>{});

CT_ASSERT(std::is_same<pmf_cv,  ct::remove_reference_qualifier<pmf_cvl>>{});
CT_ASSERT(std::is_same<pmf_cv,  ct::remove_reference_qualifier<pmf_cvr>>{});

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

CT_ASSERT(!ct::is_lvalue_reference_qualified<pmf>());
CT_ASSERT(!ct::is_lvalue_reference_qualified(pmf{}));
CT_ASSERT(ct::is_lvalue_reference_qualified<pmf_l>());
CT_ASSERT(ct::is_lvalue_reference_qualified(pmf_l{}));
CT_ASSERT(!ct::is_lvalue_reference_qualified<pmf_r>());
CT_ASSERT(!ct::is_lvalue_reference_qualified(pmf_r{}));
CT_ASSERT(!ct::is_lvalue_reference_qualified<pmf_c>());
CT_ASSERT(!ct::is_lvalue_reference_qualified(pmf_c{}));
CT_ASSERT(ct::is_lvalue_reference_qualified<pmf_cl>());
CT_ASSERT(ct::is_lvalue_reference_qualified(pmf_cl{}));
CT_ASSERT(!ct::is_lvalue_reference_qualified<pmf_cr>());
CT_ASSERT(!ct::is_lvalue_reference_qualified(pmf_cr{}));
CT_ASSERT(!ct::is_lvalue_reference_qualified<pmf_v>());
CT_ASSERT(!ct::is_lvalue_reference_qualified(pmf_v{}));
CT_ASSERT(ct::is_lvalue_reference_qualified<pmf_vl>());
CT_ASSERT(ct::is_lvalue_reference_qualified(pmf_vl{}));
CT_ASSERT(!ct::is_lvalue_reference_qualified<pmf_vr>());
CT_ASSERT(!ct::is_lvalue_reference_qualified(pmf_vr{}));
CT_ASSERT(!ct::is_lvalue_reference_qualified<pmf_cv>());
CT_ASSERT(!ct::is_lvalue_reference_qualified(pmf_cv{}));
CT_ASSERT(ct::is_lvalue_reference_qualified<pmf_cvl>());
CT_ASSERT(ct::is_lvalue_reference_qualified(pmf_cvl{}));
CT_ASSERT(!ct::is_lvalue_reference_qualified<pmf_cvr>());
CT_ASSERT(!ct::is_lvalue_reference_qualified(pmf_cvr{}));

CT_ASSERT(!ct::is_rvalue_reference_qualified<pmf>());
CT_ASSERT(!ct::is_rvalue_reference_qualified(pmf{}));
CT_ASSERT(!ct::is_rvalue_reference_qualified<pmf_l>());
CT_ASSERT(!ct::is_rvalue_reference_qualified(pmf_l{}));
CT_ASSERT(ct::is_rvalue_reference_qualified<pmf_r>());
CT_ASSERT(ct::is_rvalue_reference_qualified(pmf_r{}));
CT_ASSERT(!ct::is_rvalue_reference_qualified<pmf_c>());
CT_ASSERT(!ct::is_rvalue_reference_qualified(pmf_c{}));
CT_ASSERT(!ct::is_rvalue_reference_qualified<pmf_cl>());
CT_ASSERT(!ct::is_rvalue_reference_qualified(pmf_cl{}));
CT_ASSERT(ct::is_rvalue_reference_qualified<pmf_cr>());
CT_ASSERT(ct::is_rvalue_reference_qualified(pmf_cr{}));
CT_ASSERT(!ct::is_rvalue_reference_qualified<pmf_v>());
CT_ASSERT(!ct::is_rvalue_reference_qualified(pmf_v{}));
CT_ASSERT(!ct::is_rvalue_reference_qualified<pmf_vl>());
CT_ASSERT(!ct::is_rvalue_reference_qualified(pmf_vl{}));
CT_ASSERT(ct::is_rvalue_reference_qualified<pmf_vr>());
CT_ASSERT(ct::is_rvalue_reference_qualified(pmf_vr{}));
CT_ASSERT(!ct::is_rvalue_reference_qualified<pmf_cv>());
CT_ASSERT(!ct::is_rvalue_reference_qualified(pmf_cv{}));
CT_ASSERT(!ct::is_rvalue_reference_qualified<pmf_cvl>());
CT_ASSERT(!ct::is_rvalue_reference_qualified(pmf_cvl{}));
CT_ASSERT(ct::is_rvalue_reference_qualified<pmf_cvr>());
CT_ASSERT(ct::is_rvalue_reference_qualified(pmf_cvr{}));

int main() { return 0; }
