/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_ARGS_HPP
#define CALLABLE_TRAITS_REMOVE_ARGS_HPP

#include <callable_traits/detail/core.hpp>

//[ remove_args_hpp
/*`
[section:ref_remove_args remove_args]
[heading Header]
``#include<callable_traits/remove_args.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<std::size_t Index, typename T, std::size_t Count = 1>
    using remove_args_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::template remove_args<Index, Count>,
            cannot_determine_parameters_for_this_type>;
    //->

    template<std::size_t Index, typename T, std::size_t Count = 1>
    struct remove_args {
        using type = remove_args_t<Index, T, Count>;
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
* The aliased type is identical to `T`, except that `Count` number of types in the parameter list of `T`, starting at zero-based `Index`, do not exist in the parameter list of the aliased type.
*
[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_args_t<1, T, 2>`]]
    [[`int(A, B, C, D)`]                [`int(A, D)`]]
    [[`int(*)(A, B, C, D)`]             [`int(*)(A, D)`]]
    [[`int(&)(A, B, C, D)`]             [`int(&)(A, D)`]]
    [[`int(foo::*)(A, B, C, D)`]        [`int(foo::*)(A, B, C, D)`]]
]

[heading Example Program]
[import ../example/remove_args.cpp]
[remove_args]
[endsect]
*/
//]

#endif //CALLABLE_TRAITS_REMOVE_ARGS_HPP
