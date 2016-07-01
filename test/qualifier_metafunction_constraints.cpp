
#include <callable_traits/callable_traits.hpp>
#include "test.hpp"

struct foo;

int main() {

#define CALLABLE_TRAIT_UNDER_TEST add_member_const_t
#include "qualifier_metafunction_constraints.hpp"
#undef CALLABLE_TRAIT_UNDER_TEST

#define CALLABLE_TRAIT_UNDER_TEST remove_member_const_t
#include "qualifier_metafunction_constraints.hpp"
#undef CALLABLE_TRAIT_UNDER_TEST

#define CALLABLE_TRAIT_UNDER_TEST add_member_volatile_t
#include "qualifier_metafunction_constraints.hpp"
#undef CALLABLE_TRAIT_UNDER_TEST

#define CALLABLE_TRAIT_UNDER_TEST remove_member_volatile_t
#include "qualifier_metafunction_constraints.hpp"
#undef CALLABLE_TRAIT_UNDER_TEST

#define CALLABLE_TRAIT_UNDER_TEST add_member_cv_t
#include "qualifier_metafunction_constraints.hpp"
#undef CALLABLE_TRAIT_UNDER_TEST

#define CALLABLE_TRAIT_UNDER_TEST remove_member_cv_t
#include "qualifier_metafunction_constraints.hpp"
#undef CALLABLE_TRAIT_UNDER_TEST

#ifndef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

#define CALLABLE_TRAIT_UNDER_TEST add_member_lvalue_reference_t
#include "qualifier_metafunction_constraints.hpp"
#undef CALLABLE_TRAIT_UNDER_TEST

#define CALLABLE_TRAIT_UNDER_TEST add_member_rvalue_reference_t
#include "qualifier_metafunction_constraints.hpp"
#undef CALLABLE_TRAIT_UNDER_TEST

#define CALLABLE_TRAIT_UNDER_TEST remove_member_reference_t
#include "qualifier_metafunction_constraints.hpp"
#undef CALLABLE_TRAIT_UNDER_TEST

#endif

}

