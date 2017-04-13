/*
 *
@copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_VOLATILE_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_VOLATILE_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ is_volatile_member_hpp
/*`[section:ref_is_volatile_member is_volatile_member]
[heading Header]
``#include <boost/callable_traits/is_volatile_member.hpp>``
[heading Definition]
*/


template<typename T>
struct is_volatile_member; //implementation-defined

//<-
template<typename T>
struct is_volatile_member : detail::traits<T>::is_volatile_member {
    using type = typename detail::traits<T>::is_volatile_member;
};
//->

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_volatile_member_v {
    static_assert(sizeof(T) < 1,
        "Variable templates not supported on this compiler.");
};

#else

template<typename T>
constexpr bool is_volatile_member_v = //implementation-defined
//<-
    detail::traits<T>::is_volatile_member::value;
//->

#endif
//<-
BOOST_CLBL_TRTS_NAMESPACE_END
//->


/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `is_volatile_member<T>` and is aliased by `typename is_volatile_member<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function type with a `volatile` member qualifier
  * `T` is a pointer to a member function with a `volatile` member qualifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `volatile` member qualifier
* On compilers that support variable templates, `is_volatile_member_v<T>` is equivalent to `is_volatile_member<T>::value`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_volatile_member_v<T>`]]
    [[`int() volatile`]                 [`true`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() volatile &&`]              [`true`]]
    [[`int(foo::*)() volatile`]         [`true`]]
    [[`int(foo::*)() const volatile`]   [`true`]]
    [[`int(foo::*)() const volatile &&`][`true`]]
    [[`int()`]                          [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int(foo::* const)() volatile`]   [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`volatile int foo::*`]            [`false`]]
]

[heading Example Program]
[import ../example/is_volatile_member.cpp]
[is_volatile_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_VOLATILE_MEMBER_HPP
