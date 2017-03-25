/*
@file is_noexcept

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_NOEXCEPT_HPP
#define BOOST_CLBL_TRTS_IS_NOEXCEPT_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ is_noexcept_hpp
/*`[section:ref_is_noexcept is_noexcept]
[heading Header]
``#include <boost/callable_traits/is_noexcept.hpp>``
[heading Definition]
*/

template<typename T>
struct is_noexcept; //implementation-defined

//<-
template<typename T>
struct is_noexcept : detail::traits<T>::is_noexcept {
    using type = typename detail::traits<T>::is_noexcept;
};
//->

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_noexcept_v {
    static_assert(sizeof(T) < 1,
        "Variable templates not supported on this compiler.");
};

#else

template<typename T>
constexpr bool is_noexcept_v = //implementation-defined
//<-
    detail::traits<T>::is_noexcept::value;
//->
#endif

//<-
BOOST_CLBL_TRTS_NAMESPACE_END
//->

/*`
[heading Constraints]
* none
*
[heading Behavior]
* `std::false_type` is inherited by `is_noexcept<T>` and is aliased by `typename is_noexcept<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function type, function pointer type, function reference type, or member function pointer type where the function has a `noexcept` specifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `noexcept` specifier
* On compilers that support variable templates, `is_noexcept_v<T>` is equivalent to `is_noexcept<T>::value`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+. Obviously, this will always be falsy for compilers that don't support `noexcept` at all.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_noexcept_v<T>`]]
    [[`int() const noexcept`]           [`true`]]
    [[`int(*)() noexcept`]              [`true`]]
    [[`int(&)() noexcept`]              [`true`]]
    [[`int(foo::*)() noexcept`]         [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::*)() const`]            [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &`]                        [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_noexcept.cpp]
[is_noexcept]
[endsect]
*/
//]

#endif //#ifndef BOOST_CLBL_TRTS_IS_NOEXCEPT_HPP
