/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_INSERT_ARGS_HPP
#define CALLABLE_TRAITS_INSERT_ARGS_HPP

#include <callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

//[ insert_args_hpp
/*`[section:ref_insert_args insert_args]
[heading Header]
``#include<callable_traits/insert_args.hpp>``
[heading Definition]
*/


    template<std::size_t Index, typename T, typename... Args>
    using insert_args_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::template insert_args<Index, Args...>,
            cannot_determine_parameters_for_this_type>;
    //->

    template<std::size_t Index, typename T, typename... Args>
    struct insert_args {
        using type = insert_args_t<Index, T, Args...>;
    };
//<-
CALLABLE_TRAITS_NAMESPACE_END
//->



/*`
[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type
* `Index` must be less than or equal to the number of parameters in the parameter list of `T`

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* The aliased type is identical to `T`, except that `Args...` are inserted into the parameter list of `T`, at `Index` (zero-based).

[heading Input/Output Examples]
[table
    [[`T`]                              [`insert_args_t<1, T, foo, bar>`]]
    [[`int(int)`]                       [`int(int, foo, bar)`]]
    [[`int(int, char) const &`]         [`int(int, foo, bar, char) const &`]]
    [[`int(*)(int) transaction_safe`]   [`int(*)(int, foo, bar) transaction_safe`]]
    [[`int(*)(int, char)`]              [`int(*)(int, foo, bar, char)`]]
    [[`int(&)(int)`]                    [`int(&)(int, foo, bar)`]]
    [[`int(&)(int, char)`]              [`int(&)(int, foo, bar, char)`]]
    [[`int(foo::*)(int) const`]         [`int(foo::*)(int, foo, bar) const`]]
    [[`int(foo::*)(int, char)`]         [`int(foo::*)(int, foo, bar, char) const`]]
    [[`int()`]                          [(substitution failure)]]
    [[`int(foo::*)()`]                  [(substitution failure)]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (* const)()`]                [(substitution failure)]]
]

[heading Example Program]
[import ../example/insert_args.cpp]
[insert_args]
[endsect]
*/
//]

#endif //CALLABLE_TRAITS_INSERT_ARGS_HPP
