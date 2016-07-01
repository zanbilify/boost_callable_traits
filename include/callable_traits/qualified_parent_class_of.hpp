/*

@copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_QUALIFIED_PARENT_CLASS_OF_HPP
#define CALLABLE_TRAITS_QUALIFIED_PARENT_CLASS_OF_HPP

#include <callable_traits/detail/core.hpp>

//[ qualified_parent_class_of_hpp
/*`
[section:ref_qualified_parent_class_of qualified_parent_class_of]
[heading Header]
``#include<callable_traits/qualified_parent_class_of.hpp>``
[heading Definition]
*/

CALLABLE_TRAITS_NAMESPACE_BEGIN

    template<typename T>
    using qualified_parent_class_of_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::invoke_type,
            type_is_not_a_member_pointer>;
    //->

    template<typename T>
    struct qualified_parent_class_of {
        using type = qualified_parent_class_of_t<T>;
    };
//<-
CALLABLE_TRAITS_NAMESPACE_END
//->


/*`
[heading Constraints]
* `T` must be a member pointer

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* If `T` is a member function pointer, the aliased type is the parent class of the member, qualified according to the member qualifiers on `T`. If `T` does not have a member reference qualifier, then the aliased type will be an lvalue reference.
* If `T` is a member data pointer, the aliased type is equivalent to `ct::parent_class_of<T> const &`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`qualified_parent_class_of_t<T>`]]
    [[`void(foo::*)()`]                 [`foo &`]]
    [[`void(foo::*)() const`]           [`foo const &`]]
    [[`void(foo::*)() &&`]              [`foo &&`]]
    [[`void(foo::*)() volatile &&`]     [`foo volatile &&`]]
    [[`int foo::*`]                     [`foo const &`]]
    [[`const int foo::*`]               [`foo const &`]]
]

[heading Example Program]
[import ../example/qualified_parent_class_of.cpp]
[qualified_parent_class_of]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_QUALIFIED_PARENT_CLASS_OF_HPP
