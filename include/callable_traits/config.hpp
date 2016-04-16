/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CONFIG_HPP
#define CALLABLE_TRAITS_CONFIG_HPP

#define CALLABLE_TRAITS_IX_SEQ(...) ::std::index_sequence< __VA_ARGS__ >
#define CALLABLE_TRAITS_MAKE_IX_SEQ(...) ::std::make_index_sequence< __VA_ARGS__ >
#define CALLABLE_TRAITS_DISJUNCTION(...) ::std::disjunction< __VA_ARGS__ >
#define CALLABLE_TRAITS_CONJUNCTION(...) ::std::conjunction< __VA_ARGS__ >
#define CALLALBLE_TRAITS_DECLTYPE_AUTO decltype(auto)

#ifndef __cpp_decltype_auto
#undef CALLALBLE_TRAITS_DECLTYPE_AUTO
#define CALLALBLE_TRAITS_DECLTYPE_AUTO auto
#endif

#ifndef __cpp_lib_logical_traits
#include <callable_traits/detail/polyfills/conjunction.hpp>
#include <callable_traits/detail/polyfills/disjunction.hpp>
#endif //__cpp_lib_logical_traits

#ifndef __cpp_lib_integer_sequence
#include <callable_traits/detail/polyfills/make_index_sequence.hpp>
#endif // __cpp_lib_integer_sequence

#define CALLABLE_TRAITS_EMPTY_
#define CALLABLE_TRAITS_EMPTY CALLABLE_TRAITS_EMPTY_
#define CALLABLE_TRAITS_DEFAULT_VARARGS_CC



#ifdef _MSC_VER

#ifndef __clang__

#undef CALLABLE_TRAITS_DEFAULT_VARARGS_CC
#define CALLABLE_TRAITS_DEFAULT_VARARGS_CC __cdecl
#define CALLABLE_TRAITS_PMF_VARGARGS_CDECL_DEFAULT
#define CALLABLE_TRAITS_DISABLE_BIND
#define CALLABLE_TRAITS_DISABLE_CONSTEXPR_CHECKS
#define CALLABLE_TRAITS_MSVC

#if _MSC_FULL_VER == 190023918
#include <callable_traits/detail/polyfills/make_index_sequence.hpp>
#endif //#if _MSC_FULL_VER == 190023918

#endif //ifndef __clang__

#endif //_MSC_VER


#if defined __GNUC__ && __GNUC__ < 5
#define CALLABLE_TRAITS_DISABLE_CONSTEXPR_CHECKS
#endif


#ifndef CALLABLE_TRAITS_ARITY_SEARCH_LIMIT
#define CALLABLE_TRAITS_ARITY_SEARCH_LIMIT 10
#endif //CALLABLE_TRAITS_ARITY_SEARCH_LIMIT

#endif
