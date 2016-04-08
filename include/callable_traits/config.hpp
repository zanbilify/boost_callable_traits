/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CONFIG_HPP
#define CALLABLE_TRAITS_CONFIG_HPP

#define CALLABLE_TRAITS_EMPTY_
#define CALLABLE_TRAITS_EMPTY CALLABLE_TRAITS_EMPTY_

#define CALLABLE_TRAITS_DEFAULT_VARARGS_CC

#ifdef _MSC_VER

    #ifndef __clang__

    #undef CALLABLE_TRAITS_DEFAULT_VARARGS_CC
    #define CALLABLE_TRAITS_DEFAULT_VARARGS_CC __cdecl
    #define CALLABLE_TRAITS_PMF_VARGARGS_CDECL_DEFAULT
    #define CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED
    #define CALLABLE_TRAITS_MSVC

    #endif //ifndef __clang__

#endif //_MSC_VER

#ifndef CALLABLE_TRAITS_ARITY_SEARCH_LIMIT
#define CALLABLE_TRAITS_ARITY_SEARCH_LIMIT 10
#endif //CALLABLE_TRAITS_ARITY_SEARCH_LIMIT

#endif
