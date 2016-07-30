/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_MEMBER_REFERENCE_HPP
#define CALLABLE_TRAITS_REMOVE_MEMBER_REFERENCE_HPP

#include <callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

//[ remove_member_reference_hpp
/*`
[section:ref_remove_member_reference remove_member_reference]
[heading Header]
``#include<callable_traits/remove_member_reference.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_reference_t = //implementation-defined
//<-
    detail::fail_if_invalid<
        typename detail::traits<T>::remove_member_reference,
        member_qualifiers_are_illegal_for_this_type>;
//->

template<typename T>
struct remove_member_reference {
    using type = remove_member_reference_t<T>;
};

//<-
CALLABLE_TRAITS_NAMESPACE_END
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type

[heading Behavior]
* A substitution failure occuers if the constraints are violated.
* Removes member `&` or `&&` qualifiers from `T`, if present.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_const_t<T>`]]
    [[`int() &`]                        [`int()`]]
    [[`int(foo::*)() &`]                [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() const`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() const`]]
    [[`int(foo::*)()`]                  [`int(foo::*)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_reference.cpp]
[remove_member_reference]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_REMOVE_MEMBER_REFERENCE_HPP
