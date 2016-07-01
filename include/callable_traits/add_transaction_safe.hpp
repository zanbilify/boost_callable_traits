/*
@file add_transaction_safe

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_TRANSACTION_SAFE_HPP
#define CALLABLE_TRAITS_ADD_TRANSACTION_SAFE_HPP

#include <callable_traits/detail/core.hpp>

//[ add_transaction_safe_hpp
/*`
[section:ref_add_transaction_safe add_transaction_safe]
[heading Header]
``#include<callable_traits/add_transaction_safe.hpp>``
[heading Definition]
*/

CALLABLE_TRAITS_NAMESPACE_BEGIN

    template<typename T>
    using add_transaction_safe_t = //implementation-defined
//<-
#ifdef CALLABLE_TRAITS_ENABLE_TRANSACTION_SAFE

        detail::fail_if_invalid<
            typename detail::traits<T>::add_transaction_safe,
            cannot_add_transaction_safe_to_this_type>;
#else

        detail::sfinae_try<T,
            detail::fail_if<true,
                transaction_safe_is_not_enabled_on_this_platform>>;
#endif
//->

    template<typename T>
    struct add_transaction_safe {
        using type = add_transaction_safe_t<T>;
    };
//<-
CALLABLE_TRAITS_NAMESPACE_END
//->


/*`
[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a `transaction_safe` specifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_transaction_safe_t<T>`]]
    [[`int()`]                          [`int() transaction_safe`]]
    [[`int (&)()`]                      [`int(&)() transaction_safe`]]
    [[`int (*)()`]                      [`int(*)() transaction_safe`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() transaction_safe`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() & transaction_safe`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() && transaction_safe`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const transaction_safe`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (*&)()`]                     [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_transaction_safe.cpp]
[add_transaction_safe]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_ADD_TRANSACTION_SAFE_HPP
