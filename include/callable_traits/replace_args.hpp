/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REPLACE_ARGS_HPP
#define CALLABLE_TRAITS_REPLACE_ARGS_HPP

#include <callable_traits/detail/core.hpp>

//[ replace_args_hpp
/*`
[section:ref_replace_args replace_args]
[heading Header]
``#include<callable_traits/replace_args.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<std::size_t Index, typename T, typename... Args>
    using replace_args_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::template replace_args<Index, Args...>,
            cannot_determine_parameters_for_this_type>;
    //->

    template<std::size_t Index, typename T, typename... Args>
    struct replace_args {
        using type = replace_args_t<Index, T, Args...>;
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
* The aliased type is identical to `T`, except that the parameter list types are "overwritten" by `Args...`, beginning at zero-based `Index`.
* * If `sizeof...(Args)` is greater than then number of function parameters in `T` minus `Index`, the aliased type will contain more parameters than `T`.

[heading Input/Output Examples]
[table
    [[`T`]                                  [`replace_args_t<1, T, float, double>`]]
    [[`int(int, char) const`]               [`int(int, float, double) const`]]
    [[`int(&)(int, char)`]                  [`int(&)(int, float, double)`]]
    [[`int(*)(int, char) transaction_safe`] [`int(*)(int, float, double) transaction_safe`]]
    [[`int(foo::*)(int, char)`]             [`int(foo::*)(int, float, double)`]]
    [[`int(foo::*)(int, char) const`]       [`int(foo::*)(int, float, double) const`]]
    [[`int`]                                [(substitution failure)]]
    [[`int foo::*`]                         [(substitution failure)]]
    [[`int (* const)()`]                    [(substitution failure)]]
]

[heading Example Program]
[import ../example/replace_args.cpp]
[replace_args]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_REPLACE_ARGS_HPP
