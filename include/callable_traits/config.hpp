/*!
@copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CONFIG_HPP
 #define CALLABLE_TRAITS_CONFIG_HPP

 #define CALLABLE_TRAITS_EMPTY_
 #define CALLABLE_TRAITS_EMPTY CALLABLE_TRAITS_EMPTY_

 #ifndef __clang__
  #if defined __GNUC__

   #define CALLABLE_TRAITS_GCC

   #if __GNUC__ < 5
     #define CALLABLE_TRAITS_GCC_OLDER_THAN_5_0_0
   #endif

   #if __GNUC__ >= 5
    #define CALLABLE_TRAITS_GCC_AT_LEAST_4_9_2
   #elif __GNUC__ == 4 && __GNUC_MINOR__ == 9 && __GNUC_PATCHLEVEL__ >= 2
    #define CALLABLE_TRAITS_GCC_AT_LEAST_4_9_2
   #else
    #define CALLABLE_TRAITS_GCC_OLDER_THAN_4_9_2
   #endif //#if __GNUC__ >= 5

  #endif //#if defined __GNUC__
 #endif //#ifndef __clang__

 #ifdef _MSC_VER
  #ifdef __clang__
   #define CALLABLE_TRAITS_CLANG_C2
  #else
   #define CALLABLE_TRAITS_MSVC
  #endif //#ifdef __clang__
 #endif //#ifdef _MSC_VER

 #define CALLABLE_TRAITS_IX_SEQ(...) ::std::index_sequence< __VA_ARGS__ >
 #define CALLABLE_TRAITS_MAKE_IX_SEQ(...) ::std::make_index_sequence< __VA_ARGS__ >
 #define CALLABLE_TRAITS_DISJUNCTION(...) ::std::disjunction< __VA_ARGS__ >
 #define CALLABLE_TRAITS_CONJUNCTION(...) ::std::conjunction< __VA_ARGS__ >
 #define CALLALBLE_TRAITS_DECLTYPE_AUTO decltype(auto)

#ifndef __cpp_variable_templates
#define CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES
#endif

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

 #ifdef CALLABLE_TRAITS_MSVC

  #define CALLABLE_TRAITS_DEFAULT_VARARGS_CC __cdecl
  #define CALLABLE_TRAITS_PMF_VARGARGS_CDECL_DEFAULT

  //Visual Studio 2015 Update 2 broke std::make_index_sequence
  #if _MSC_FULL_VER == 190023918
  #include <callable_traits/detail/polyfills/make_index_sequence.hpp>
  #endif //#if _MSC_FULL_VER == 190023918

 #else //#ifdef CALLABLE_TRAITS_MSVC
  #define CALLABLE_TRAITS_DEFAULT_VARARGS_CC
 #endif //#ifdef CALLABLE_TRAITS_MSVC

 #ifdef CALLABLE_TRAITS_GCC

 #ifndef CALLABLE_TRAITS_GCC_AT_LEAST_4_9_2
  #define CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
  #define CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS
 #endif //#ifndef CALLABLE_TRAITS_GCC_AT_LEAST_4_9_2

 #endif//#ifdef CALLABLE_TRAITS_GCC

 #ifdef CALLABLE_TRAITS_GCC_OLDER_THAN_4_9_2
  #define CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS
  #define CALLABLE_TRAITS_ABOMINABLE_CONST CALLABLE_TRAITS_EMPTY
  #define CALLABLE_TRAITS_ABOMINABLE_VOLATILE CALLABLE_TRAITS_EMPTY
 #else
  #define CALLABLE_TRAITS_ABOMINABLE_CONST const
  #define CALLABLE_TRAITS_ABOMINABLE_VOLATILE volatile
 #endif //#ifdef CALLABLE_TRAITS_GCC_OLDER_THAN_4_9_2

 #endif //#ifndef CALLABLE_TRAITS_CONFIG_HPP
