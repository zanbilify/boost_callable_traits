/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_PUSH_FRONT_ARGS_HPP
#define CALLABLE_TRAITS_PUSH_FRONT_ARGS_HPP

#include <callable_traits/detail/core.hpp>

//[ push_front_args_hpp
/*`
[section:ref_push_front_args push_front_args]
[heading Header]
``#include<callable_traits/push_front_args.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T, typename... Args>
    using push_front_args_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::template push_front<Args...>,
            cannot_determine_parameters_for_this_type>;
    //->

    template<typename T, typename... Args>
    struct push_front_args {
        using type = push_front_args_t<T, Args...>;
    };
}

/*`
[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* The aliased type is identical to `T`, except that `Args...` types have been added to the front of the parameter list.
*
[heading Input/Output Examples]
[table
    [[`T`]                              [`push_front_args_t<T, float, double>`]]
    [[`int(char)`]                      [`int(float, double, char)`]]
    [[`int(*)(char)`]                   [`int(*)(float, double, char)`]]
    [[`int(&)(char)`]                   [`int(&)(float, double, char)`]]
    [[`int(foo::*)(char) volatile`]     [`int(foo::*)(float, double, char) volatile`]]
]

[heading Example Program]
[import ../example/push_front_args.cpp]
[push_front_args]
[endsect]
*/
//]

#endif //CALLABLE_TRAITS_PUSH_FRONT_ARGS_HPP
