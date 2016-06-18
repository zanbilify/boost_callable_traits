/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_CV_MEMBER_HPP
#define CALLABLE_TRAITS_IS_CV_MEMBER_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/core.hpp>

//[ is_cv_member_hpp
/*`[section:ref_is_cv_member is_cv_member]
[heading Header]
``#include<callable_traits/is_cv_member.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T>
    struct is_cv_member; //implementation-defined

    //<-
    template<typename T>
    struct is_cv_member
        : detail::traits<T>::is_cv_member {

        using type = typename detail::traits<T>::is_cv_member;
    };

    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T>
    struct is_cv_member_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else
    //->
    template<typename T>
    constexpr bool is_cv_member_v = //implementation-defined
    //<-
        detail::traits<T>::is_cv_member::value;

    #endif
    //->
}
/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `is_cv_member<T>` and is aliased by `typename is_cv_member<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function type with both `const` and `volatile` member qualifiers
  * `T` is a pointer to a member function with both `const` and `volatile` member qualifiers
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has both `const` and `volatile` member qualifiers
* On compilers that support variable templates, `is_cv_member_v<T>` is equivalent to `is_cv_member<T>::value`.

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

#endif
