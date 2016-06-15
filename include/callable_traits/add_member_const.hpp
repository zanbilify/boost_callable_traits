/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_MEMBER_CONST_HPP
#define CALLABLE_TRAITS_ADD_MEMBER_CONST_HPP

#include <callable_traits/detail/core.hpp>

//[ add_member_const_hpp
//`[section:ref_add_member_const add_member_const]

namespace callable_traits {

    template<typename T>
    struct add_member_const {

        using type = //implementation-defined
        //<-
            detail::fail_if_invalid<
                typename detail::traits<T>::add_member_const,
                member_qualifiers_are_illegal_for_this_type>;
        //->
    };

    template<typename T>
    using add_member_const_t = typename add_member_const<T>::type;
}

/*`
[heading Constraints]
* `T` must be a function or a member function pointer

[heading Behavior]
* Adds a member `const` qualifier to `T`, if not already present
*
[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_const_t<T>`]]
    [[`int()`]                          [`int() const`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() const`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() const &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() const &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() const transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_const.cpp]
[add_member_const]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_ADD_MEMBER_CONST_HPP



