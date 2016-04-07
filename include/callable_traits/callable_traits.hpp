/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CALLABLE_TRAITS_HPP
#define CALLABLE_TRAITS_CALLABLE_TRAITS_HPP

#include <callable_traits/add_const_qualifier.hpp>
#include <callable_traits/add_cv_qualifiers.hpp>
#include <callable_traits/add_lvalue_qualifier.hpp>
#include <callable_traits/add_rvalue_qualifier.hpp>
#include <callable_traits/add_varargs.hpp>
#include <callable_traits/add_volatile_qualifier.hpp>
#include <callable_traits/apply_member_pointer.hpp>
#include <callable_traits/apply_return.hpp>
#include <callable_traits/arg_at.hpp>
#include <callable_traits/args.hpp>
#include <callable_traits/arity.hpp>
#include <callable_traits/bind.hpp>
#include <callable_traits/can_invoke.hpp>
#include <callable_traits/can_invoke_constexpr.hpp>
#include <callable_traits/function_type.hpp>
#include <callable_traits/has_varargs.hpp>
#include <callable_traits/has_void_return.hpp>
#include <callable_traits/is_const_qualified.hpp>
#include <callable_traits/is_constexpr.hpp>
#include <callable_traits/is_lvalue_qualified.hpp>
#include <callable_traits/is_reference_qualified.hpp>
#include <callable_traits/is_rvalue_qualified.hpp>
#include <callable_traits/is_unqualified.hpp>
#include <callable_traits/is_volatile_qualified.hpp>
#include <callable_traits/max_arity.hpp>
#include <callable_traits/min_arity.hpp>
#include <callable_traits/qualified_function_type.hpp>
#include <callable_traits/remove_const_qualifier.hpp>
#include <callable_traits/remove_cv_qualifiers.hpp>
#include <callable_traits/remove_member_pointer.hpp>
#include <callable_traits/remove_reference_qualifier.hpp>
#include <callable_traits/remove_varargs.hpp>
#include <callable_traits/remove_volatile_qualifier.hpp>
#include <callable_traits/result_of.hpp>
#include <callable_traits/detail/required_definitions.hpp>

#endif
