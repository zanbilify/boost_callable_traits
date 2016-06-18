/*!
@file is_transaction_safe

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_TRANSACTION_SAFE_HPP
#define CALLABLE_TRAITS_IS_TRANSACTION_SAFE_HPP

#include <callable_traits/detail/core.hpp>

//[ is_transaction_safe_hpp
/*`[section:ref_is_transaction_safe is_transaction_safe]
[heading Header]
``#include<callable_traits/is_transaction_safe.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T>
    struct is_transaction_safe; //implementation-defined

    //<-
    template<typename T>
    struct is_transaction_safe
        : detail::traits<T>::is_transaction_safe {

        using type = typename detail::traits<T>::is_transaction_safe;
    };

    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T>
    struct is_transaction_safe_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else
    //->
    template<typename T>
    constexpr bool is_transaction_safe_v = //implementation-defined
    //<-
        detail::traits<T>::is_transaction_safe::value;

    #endif
    //->
}
/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `is_transaction_safe<T>` and is aliased by `typename is_transaction_safe<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function type, function pointer type, function reference type, or member function pointer type where the function has a `transaction_safe` specifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `transaction_safe` specifier
* On compilers that support variable templates, `is_transaction_safe_v<T>` is equivalent to `is_transaction_safe<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_transaction_safe_v<T>`]]
    [[`int() const transaction_safe`]   [`true`]]
    [[`int(*)() transaction_safe`]      [`true`]]
    [[`int(&)() transaction_safe`]      [`true`]]
    [[`int(foo::*)() transaction_safe`] [`true`]]
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
[import ../example/is_transaction_safe.cpp]
[is_transaction_safe]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_IS_TRANSACTION_SAFE_HPP
