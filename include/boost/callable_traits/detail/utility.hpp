/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_UTILITY_HPP
#define CALLABLE_TRAITS_DETAIL_UTILITY_HPP

#include <boost/callable_traits/detail/sfinae_errors.hpp>
#include <boost/callable_traits/config.hpp>
#include <tuple>
#include <utility>
#include <cstdint>

CALLABLE_TRAITS_DETAIL_NAMESPACE_BEGIN

struct cdecl_tag{};
struct stdcall_tag{};
struct fastcall_tag{};
struct pascal_tag{};

struct invalid_type { invalid_type() = delete; };
struct reference_error { reference_error() = delete; };

template<typename T>
using error_type = typename std::conditional<
    std::is_reference<T>::value, reference_error, invalid_type>::type;

#ifdef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS
struct abominable_functions_not_supported_on_this_compiler{};
#endif

// used to convey "this type doesn't matter" in code
struct dummy {};

// used as return type in failed SFINAE tests
struct substitution_failure : std::false_type{};

template<bool Value>
using bool_type = std::integral_constant<bool, Value>;

// shorthand for std::tuple_element
template<std::size_t I, typename Tup>
using at = typename std::tuple_element<I, Tup>::type;

template<typename T, typename Class>
using add_member_pointer = T Class::*;

template<typename L, typename R, typename ErrorType>
 using fail_when_same = fail_if<std::is_same<L, R>::value, ErrorType>;

template<typename T, typename ErrorType,
	typename U = typename std::remove_reference<T>::type>
using try_but_fail_if_invalid = sfinae_try<T,
	fail_when_same<U, invalid_type, ErrorType>,
	fail_when_same<U, reference_error, reference_type_not_supported_by_this_metafunction>>;

template<typename T, typename ErrorType,
	typename U = typename std::remove_reference<T>::type,
	bool is_reference_error = std::is_same<reference_error, U>::value>
using fail_if_invalid = fail_if<
	std::is_same<U, invalid_type>::value || is_reference_error,
	typename std::conditional<is_reference_error,
		reference_type_not_supported_by_this_metafunction, ErrorType>::type>;

template<typename T, typename Fallback>
using fallback_if_invalid = typename std::conditional<
    std::is_same<T, invalid_type>::value, Fallback, T>::type;

CALLABLE_TRAITS_DETAIL_NAMESPACE_END

#endif
