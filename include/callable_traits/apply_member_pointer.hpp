/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_APPLY_MEMBER_POINTER_HPP
#define CALLABLE_TRAITS_APPLY_MEMBER_POINTER_HPP

#include <callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(apply_member_pointer)
CALLABLE_TRAITS_SFINAE_MSG(apply_member_pointer, members_cannot_have_a_type_of_void)
CALLABLE_TRAITS_SFINAE_MSG(apply_member_pointer, second_template_argument_must_be_a_class_or_struct)

namespace detail {

    template<typename T, typename C, bool = std::is_class<C>::value>
    struct make_member_pointer;

    template<typename T, typename C>
    struct make_member_pointer<T, C, true> {
        using type = typename std::remove_reference<T>::type C::*;
    };

    template<typename C>
    struct make_member_pointer<void, C, true> {
        using type = invalid_type;
    };

    template<typename T, typename C>
    struct make_member_pointer<T, C, false> {
        using type = invalid_type;
    };

    template<typename T, typename C>
    using make_member_pointer_t = typename make_member_pointer<T, C>::type;
}

//[ apply_member_pointer_hpp
/*`
[section:ref_apply_member_pointer apply_member_pointer]
[heading Header]
``#include<callable_traits/apply_member_pointer.hpp>``
[heading Definition]
*/

template<typename T, typename C>
using apply_member_pointer_t = //implementation-defined
//<-
    detail::sfinae_try<
        detail::fallback_if_invalid<
            typename detail::traits<T>::template apply_member_pointer<C>,
            typename detail::make_member_pointer<T, C>::type>,

        detail::fail_if<std::is_same<void, T>::value,
            members_cannot_have_a_type_of_void>,

        detail::fail_if<!std::is_class<C>::value,
            second_template_argument_must_be_a_class_or_struct> >;
//->

template<typename T, typename C>
struct apply_member_pointer {
    using type = apply_member_pointer_t<T, C>;
};

//<-
CALLABLE_TRAITS_NAMESPACE_END
//->

/*`
[heading Constraints]
* `T` may be any type except `void`
* `C` must be a user-defined type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* When `T` is a function, function pointer, or function reference, then the aliased type is a member function pointer of `C` with the same parameters and return type.
* When `T` is a member function pointer of any type, the aliased type is a member function pointer of `C` with the same parameters and return type.
* Otherwise, the aliased type is a member data pointer equivalent to `std::remove_reference_t<T> C::*`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

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
    [[`int`]                            [`int foo::*`]]
    [[`int &`]                          [`int foo::*`]]
    [[`const int &`]                    [`const int foo::*`]]
    [[`int (*const)()`]                 [`int (*const foo::*)()`]]
    [[`void`]                           [(substitution failure)]]
]

[heading Example Program]
[import ../example/apply_member_pointer.cpp]
[apply_member_pointer]
[endsect]
*/
//]
#endif
