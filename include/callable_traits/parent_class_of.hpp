/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_PARENT_CLASS_OF_HPP
#define CALLABLE_TRAITS_PARENT_CLASS_OF_HPP

#include <callable_traits/detail/core.hpp>

//[ parent_class_of_hpp
/*`
[section:ref_parent_class_of parent_class_of]
[heading Header]
``#include<callable_traits/parent_class_of.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T>
    using parent_class_of_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::class_type,
            type_is_not_a_member_pointer>;
    //->

    template<typename T>
    struct parent_class_of {
        using type = parent_class_of_t<T>;
    };
}

/*`
[heading Constraints]
* `T` must be a member pointer

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* The aliased type is the parent class of the member. In other words, if `T` is expanded to `U C::*`, the aliased type is `C`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`parent_class_of_t<T>`]]
    [[`int foo::*`]                     [`foo`]]
    [[`void(foo::*)() const`]           [`foo`]]
]

[heading Example Program]
[import ../example/parent_class_of.cpp]
[parent_class_of]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_PARENT_CLASS_OF_HPP
