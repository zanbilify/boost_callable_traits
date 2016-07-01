/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CLEAR_ARGS_HPP
#define CALLABLE_TRAITS_CLEAR_ARGS_HPP

#include <callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

//[ clear_args_hpp
/*`[section:ref_clear_args clear_args]
[heading Header]
``#include<callable_traits/clear_args.hpp>``
[heading Definition]
*/


    template<typename T>
    using clear_args_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::clear_args,
            cannot_clear_the_parameter_list_for_this_type>;
    //->

    template<typename T>
    struct clear_args {
        using type = clear_args_t<T>;
    };
//<-
CALLABLE_TRAITS_NAMESPACE_END
//->


/*`
[heading Constraints]
* `T` must be one of the following:
  * function
  * function pointer
  * function reference
  * member function pointer

[heading Behavior]
* When the constraints are violated, a substitution failure occurs.
* The aliased type has an empty parameter list, but is otherwise identical to `T`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`clear_args_t<T>`]]
    [[`void(float, char, int)`]         [`void()`]]
    [[`void(*)(float, char, int)`]      [`void(*)()`]]
    [[`void(&)(float, char, int)`]      [`void(&)()`]]
    [[`void(float, char, int) const &&`][`void() const &&`]]
    [[`void(*)()`]                      [`void(*)()`]]
    [[`void(foo::*)(float, char, int)`] [`void(foo::*)()`]]
    [[`int(foo::*)(int) const`]         [`int(foo::*)() const`]]
    [[`void(foo::*)() volatile &&`]     [`void(foo::*)() volatile &&`]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/clear_args.cpp]
[clear_args]
[endsect]
*/
//]

#endif //CALLABLE_TRAITS_CLEAR_ARGS_HPP
