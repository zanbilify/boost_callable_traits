/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_MEMBER_CV_HPP
#define CALLABLE_TRAITS_ADD_MEMBER_CV_HPP

#include <callable_traits/detail/core.hpp>

//[ add_member_cv_hpp
/*`
[section:ref_add_member_cv add_member_cv]
[heading Header]
``#include<callable_traits/add_member_cv.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T>
    using add_member_cv_t = //implementation-defined
//<-
        detail::fail_if_invalid<
            typename detail::traits<T>::add_member_cv,
            member_qualifiers_are_illegal_for_this_type>;
//->

    template<typename T>
    struct add_member_cv {
        using type = add_member_cv_t<T>;
    };
}

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds member `const` and `volatile` qualifiers to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_cv_t<T>`]]
    [[`int()`]                          [`int() const volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() const volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() const volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() const volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_cv.cpp]
[add_member_cv]
[endsect]
*/
//]

#endif
