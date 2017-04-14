/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP
#define BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ has_member_qualifiers_hpp
/*`[section:ref_has_member_qualifiers has_member_qualifiers]
[heading Header]
``#include <boost/callable_traits/has_member_qualifiers.hpp>``
[heading Definition]
*/

template<typename T>
struct has_member_qualifiers; //immplementation-defined

//<-
template<typename T>
struct has_member_qualifiers : detail::traits<T>::has_member_qualifiers {
    using type = typename detail::traits<T>::has_member_qualifiers;
};

// older compilers don't support variable templates
#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_member_qualifiers_v {
    static_assert(sizeof(T) < 1,
        "Variable templates not supported on this compiler.");
};

#else
//->
template<typename T>
constexpr bool has_member_qualifiers_v = //see below
//<-
    detail::traits<T>::has_member_qualifiers::value;

#endif
//->

//<-
BOOST_CLBL_TRTS_NAMESPACE_END
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_member_qualifiers<T>` and is aliased by `typename has_member_qualifiers<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function with member qualifiers
  * `T` is a member function pointer with member qualifiers
  * `T` is a function object with a member-qualified `operator()`
* On compilers that support variable templates, `has_member_qualifiers_v<T>` is equivalent to `has_member_qualifiers<T>::value`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_member_qualifiers_v<T>`]]
    [[`void() const`]                   [`true`]]
    [[`void() const transaction_safe`]  [`true`]]
    [[`void() volatile &&`]             [`true`]]
    [[`int(foo::*)() &`]                [`true`]]
    [[`void(foo::*)() const`]           [`true`]]
    [[`void(foo::*&)() const`]          [`false`]]
    [[`void(foo::* const)() const`]     [`false`]]
    [[`void()`]                         [`false`]]
    [[`void() transaction_safe`]        [`false`]]
    [[`void(*)()`]                      [`false`]]
    [[`void(*&)()`]                     [`false`]]
    [[`int`]                            [`false`]]
    [[`const int`]                      [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/has_member_qualifiers.cpp]
[has_member_qualifiers]
[endsect]
*/
//]

#endif //BOOST_CLBL_TRTS_HAS_MEMBER_QUALIFIERS_HPP
