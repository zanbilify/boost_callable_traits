/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define CALLABLE_TRAITS_INCLUDE_NOEXCEPT
#define CALLABLE_TRAITS_IS_NOEXCEPT std::false_type
#include <boost/callable_traits/detail/unguarded/function_3.hpp>

#undef CALLABLE_TRAITS_INCLUDE_NOEXCEPT
#undef CALLABLE_TRAITS_IS_NOEXCEPT

#ifdef CALLABLE_TRAITS_ENABLE_NOEXCEPT_TYPES

#define CALLABLE_TRAITS_IS_NOEXCEPT std::true_type
#define CALLABLE_TRAITS_INCLUDE_NOEXCEPT noexcept
#include <boost/callable_traits/detail/unguarded/function_3.hpp>
#undef CALLABLE_TRAITS_INCLUDE_NOEXCEPT
#undef CALLABLE_TRAITS_IS_NOEXCEPT

#endif // #ifdef CALLABLE_TRAITS_ENABLE_NOEXCEPT_TYPES
