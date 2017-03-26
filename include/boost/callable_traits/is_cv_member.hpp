/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_CV_MEMBER_HPP
#define BOOST_CLBL_TRTS_IS_CV_MEMBER_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ is_cv_member_hpp
/*`[section:ref_is_cv_member is_cv_member]
[heading Header]
``#include <boost/callable_traits/is_cv_member.hpp>``
[heading Definition]
*/

template<typename T>
struct is_cv_member; //implementation-defined

//<-
template<typename T>
struct is_cv_member
    : detail::traits<T>::is_cv_member {
    using type = typename detail::traits<T>::is_cv_member;
};
//->

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_cv_member_v {
    static_assert(sizeof(T) < 1,
        "Variable templates not supported on this compiler.");
};

#else

template<typename T>
constexpr bool is_cv_member_v = //implementation-defined
//<-
    detail::traits<T>::is_cv_member::value;
//->

#endif

//<-
BOOST_CLBL_TRTS_NAMESPACE_END
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `is_cv_member<T>` and is aliased by `typename is_cv_member<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function type with both `const` and `volatile` member qualifiers
  * `T` is a pointer to a member function with both `const` and `volatile` member qualifiers
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has both `const` and `volatile` member qualifiers
* On compilers that support variable templates, `is_cv_member_v<T>` is equivalent to `is_cv_member<T>::value`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_cv_member_v<T>`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() const volatile &`]         [`true`]]
    [[`int(foo::*)() const volatile`]   [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::*)() const`]            [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_cv_member.cpp]
[is_cv_member]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_CV_MEMBER_HPP
