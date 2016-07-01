/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_MEMBER_LVALUE_REFERENCE_HPP
#define CALLABLE_TRAITS_ADD_MEMBER_LVALUE_REFERENCE_HPP

#include <callable_traits/detail/core.hpp>

//[ add_member_lvalue_reference_hpp
/*`
[section:ref_add_member_lvalue_reference add_member_lvalue_reference]
[heading Header]
``#include<callable_traits/add_member_lvalue_reference.hpp>``
[heading Definition]
*/

CALLABLE_TRAITS_NAMESPACE_BEGIN

    template<typename T>
    using add_member_lvalue_reference_t = //implementation-defined
//<-
        detail::fail_if_invalid<
            typename detail::traits<T>::add_member_lvalue_reference,
            member_qualifiers_are_illegal_for_this_type>;
//->

    template<typename T>
    struct add_member_lvalue_reference {
        using type = add_member_lvalue_reference_t<T>;
    };
    //<-
CALLABLE_TRAITS_NAMESPACE_END
//->


/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member lvalue reference qualifier (`&`) to `T`, if not already present.
* If an rvalue reference qualifier is present, the lvalue reference qualifier replaces it (in accordance with reference collapsing rules).

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_lvalue_reference_t<T>`]]
    [[`int()`]                          [`int() &`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() &`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() &`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const &`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() & transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_lvalue_reference.cpp]
[add_member_lvalue_reference]
[endsect]
*/
//]

#endif

