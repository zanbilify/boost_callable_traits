/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_VOID_RETURN_HPP
#define BOOST_CLBL_TRTS_HAS_VOID_RETURN_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ has_void_return_hpp
/*`[section:ref_has_void_return has_void_return]
[heading Header]
``#include <boost/callable_traits/has_void_return.hpp>``
[heading Definition]
*/

template<typename T>
struct has_void_return; //see below

//<-
template<typename T>
struct has_void_return
    : std::is_same<typename detail::traits<T>::return_type, void> {};
//->

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_void_return_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else

template<typename T>
constexpr bool has_void_return_v = //see below
//<-
    std::is_same<typename detail::traits<T>::return_type, void>::value;
//->
#endif

//<-
BOOST_CLBL_TRTS_NAMESPACE_END
//->


/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_void_return<T>` and is aliased by `typename has_void_return<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function, function pointer, or function reference where the function's return type is `void`.
  * `T` is a pointer to a member function whose return type is `void`.
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` function returns `void`.
* On compilers that support variable templates, `has_void_return_v<T>` is equivalent to `has_void_return<T>::value`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_void_return_v<T>`]]
    [[`void()`]                         [`true`]]
    [[`void(int) const`]                [`true`]]
    [[`void(*)()`]                      [`true`]]
    [[`void(&)()`]                      [`true`]]
    [[`void(foo::*)() const`]           [`true`]]
    [[`int(*)()`]                       [`false`]]
    [[`int(*&)()`]                      [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`void* foo::*`]                   [`false`]]
]

[heading Example Program]
[import ../example/has_void_return.cpp]
[has_void_return]
[endsect]
*/
//]

#endif
