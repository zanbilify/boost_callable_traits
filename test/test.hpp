/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <utility>
#include <callable_traits/callable_traits.hpp>

namespace ct = callable_traits;

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
#define LREF
#define RREF
#else
#define LREF &
#define RREF &&
#endif

#define TX_SAFE CALLABLE_TRAITS_TRANSACTION_SAFE_SPECIFIER
#define VA_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC

template<template<class...> class, typename...>
struct is_substitution_failure;

template<template<class> class MetaFn, typename T>
struct is_substitution_failure<MetaFn, T> {

    template<typename>
    static auto test(...) -> std::true_type;

    template<typename U,
        typename std::remove_reference<MetaFn<U>>::type* = nullptr>
    static auto test(int) -> std::false_type;

    static constexpr bool value = decltype(test<T>(0))::value;
};

template<template<class, class> class MetaFn, typename T1, typename T2>
struct is_substitution_failure<MetaFn, T1, T2> {

    template<typename, typename>
    static auto test(...) -> std::true_type;

    template<typename A, typename B,
        typename std::remove_reference<MetaFn<A, B>>::type* = nullptr>
    static auto test(int) -> std::false_type;

    static constexpr bool value = decltype(test<T1, T2>(0))::value;
};

template<template<class, class> class Template, typename T1, typename T2>
void assert_sfinae() {
    CT_ASSERT(is_substitution_failure<Template, T1, T2>::value);
}

template<template<class> class Template, typename T>
void assert_sfinae() {
    CT_ASSERT(is_substitution_failure<Template, T>::value);
}

template<typename T1, typename T2>
void assert_same() {
    CT_ASSERT(std::is_same<T1, T2>::value);
}
