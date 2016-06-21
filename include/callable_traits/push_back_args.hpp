/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_PUSH_BACK_ARGS_HPP
#define CALLABLE_TRAITS_PUSH_BACK_ARGS_HPP

#include <callable_traits/detail/core.hpp>

//[ push_back_args_hpp
/*`
[section:ref_push_back_args push_back_args]
[heading Header]
``#include<callable_traits/push_back_args.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T, typename... Args>
    using push_back_args_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::template push_back<Args...>,
            cannot_determine_parameters_for_this_type>;
    //->

    template<typename T, typename... Args>
    struct push_back_args {
        using type = push_back_args_t<T, Args...>;
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
* The aliased type is identical to `T`, except that `Args...` types have been added to the back of the parameter list.
*
[heading Input/Output Examples]
[table
    [[`T`]                              [`push_back_args_t<T, float, double>`]]
    [[`int(char) const &&`]             [`int(char, float, double) const &&`]]
    [[`int(*)(char)`]                   [`int(*)(char, float, double)`]]
    [[`int(&)(char)`]                   [`int(&)(char, float, double)`]]
    [[`int(foo::*)(char)`]              [`int(foo::*)(char, float, double)`]]
]

[heading Example Program]
[import ../example/push_back_args.cpp]
[push_back_args]
[endsect]
*/
//]

#endif //CALLABLE_TRAITS_PUSH_BACK_ARGS_HPP
