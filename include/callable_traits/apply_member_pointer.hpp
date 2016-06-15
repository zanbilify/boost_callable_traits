/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_APPLY_MEMBER_POINTER_HPP
#define CALLABLE_TRAITS_APPLY_MEMBER_POINTER_HPP

#include <callable_traits/detail/core.hpp>

//[ apply_member_pointer_hpp
//`[section:ref_apply_member_pointer apply_member_pointer]

namespace callable_traits {

    template<typename T, typename C>
    struct apply_member_pointer {

        using type = //implementation-defined
        //<-
            detail::fallback_if_invalid<
                typename detail::traits<T>::template apply_member_pointer<C>,
                typename std::remove_reference<T>::type C::*>;
        //->
    };

    template<typename T, typename C>
    using apply_member_pointer_t =
        typename apply_member_pointer<T, C>::type;
}

/*`
[heading Constraints]
* `T` must be one of the following:
  * function
  * function pointer
  * function reference
  * member function pointer
  * member data pointer
* `C` must be a user-defined type

[heading Behavior]
* When `T` is a function, function pointer, or function reference, then the aliased type is a member function pointer of `C` with the same parameters and return type
* When `T` is a member function pointer of any type, the aliased type is a member function pointer of `C` with the same parameters and return type

[heading Input/Output Examples]
[table
    [[`T`]                              [`apply_member_pointer_t<T, foo>`]]
    [[`int()`]                          [`int(foo::*)()`]]
    [[`int (&)()`]                      [`int(foo::*)()`]]
    [[`int (*)()`]                      [`int(foo::*)()`]]
    [[`int(bar::*)()`]                  [`int(foo::*)()`]]
    [[`int(bar::*)() &`]                [`int(foo::*)() &`]]
    [[`int(bar::*)() &&`]               [`int(foo::*)() &&`]]
    [[`int(bar::*)() const`]            [`int(foo::*)() const`]]
    [[`int(bar::*)() transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int bar::*`]                     [`int foo::*`]]
    [[`int`]                            [(substitution failure)]]
    [[`bar`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/apply_member_pointer.cpp]
[apply_member_pointer]
[endsect]
*/
//]
#endif
