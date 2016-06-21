/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_MEMBER_QUALIFIERS_HPP
#define CALLABLE_TRAITS_HAS_MEMBER_QUALIFIERS_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/core.hpp>

//[ has_member_qualifiers_hpp
/*`[section:ref_has_member_qualifiers has_member_qualifiers]
[heading Header]
``#include<callable_traits/has_member_qualifiers.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T>
    struct has_member_qualifiers; //immplementation-defined

    //<-
    template<typename T>
    struct has_member_qualifiers

        : detail::traits<T>::has_member_qualifiers {
        using type = typename detail::traits<T>::has_member_qualifiers;
    };

    // older compilers don't support variable templates
    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T>
    struct has_member_qualifiers_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else
    //->
    template<typename T>
    constexpr bool has_member_qualifiers_v = //implementation-defined
    //<-
        detail::traits<T>::has_member_qualifiers::value;

    #endif
    //->
}

/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_member_qualifiers<T>` and is aliased by `typename has_member_qualifiers<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function with member qualifiers
  * `T` is a member function pointer with member qualifiers
  * `T` is a function object with a member-qualified `operator()`
* On compilers that support variable templates, `has_member_qualifiers_v<T>` is equivalent to `has_member_qualifiers<T>::value`.

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

#endif //CALLABLE_TRAITS_HAS_MEMBER_QUALIFIERS_HPP
