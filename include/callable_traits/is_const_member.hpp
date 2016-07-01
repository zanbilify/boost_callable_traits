/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_CONST_MEMBER_HPP
#define CALLABLE_TRAITS_IS_CONST_MEMBER_HPP

#include <callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

//[ is_const_member_hpp
/*`[section:ref_is_const_member is_const_member]
[heading Header]
``#include<callable_traits/is_const_member.hpp>``
[heading Definition]
*/


    template<typename T>
    struct is_const_member; //implementation-defined

    //<-
    template<typename T>
    struct is_const_member
        : detail::traits<T>::is_const_member {

        using type = typename detail::traits<T>::is_const_member;
    };

    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T>
    struct is_const_member_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else
    //->
    template<typename T>
    constexpr bool is_const_member_v = //implementation-defined
    //<-
        detail::traits<T>::is_const_member::value;

    #endif
    //->//<-
CALLABLE_TRAITS_NAMESPACE_END
//->


/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `is_const_member<T>` and is aliased by `typename is_const_member<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function type with a `const` member qualifier
  * `T` is a pointer to a member function with a `const` member qualifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `const` member qualifier
* On compilers that support variable templates, `is_const_member_v<T>` is equivalent to `is_const_member<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_const_member_v<T>`]]
    [[`int() const`]                    [`true`]]
    [[`int() const volatile`]           [`true`]]
    [[`int() const & transaction_safe`] [`true`]]
    [[`int() const &&`]                 [`true`]]
    [[`int(foo::*)() const`]            [`true`]]
    [[`int(foo::*)() const volatile`]   [`true`]]
    [[`int(foo::*)() const volatile &&`][`true`]]
    [[`int()`]                          [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &&`]                       [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int(foo::* const)() const`]      [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_const_member.cpp]
[is_const_member]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_IS_CONST_MEMBER_HPP
