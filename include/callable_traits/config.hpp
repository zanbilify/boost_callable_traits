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

#define CALLABLE_TRAITS_VARARGS_CC

#ifdef _MSC_VER

    #ifndef __clang__

    #undef CALLABLE_TRAITS_VARARGS_CC
    #define CALLABLE_TRAITS_VARARGS_CC __cdecl
    #define CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED
    #define CALLABLE_TRAITS_MSVC

    #endif //ifndef __clang__

#endif //_MSC_VER

#endif
