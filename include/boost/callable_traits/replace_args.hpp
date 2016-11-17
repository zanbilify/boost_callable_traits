/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REPLACE_ARGS_HPP
#define CALLABLE_TRAITS_REPLACE_ARGS_HPP

#include <boost/callable_traits/detail/core.hpp>
#include <boost/callable_traits/detail/parameter_index_helper.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(replace_args)
CALLABLE_TRAITS_SFINAE_MSG(replace_args, cannot_replace_parameters_in_this_type)

//[ replace_args_hpp
/*`
[section:ref_replace_args replace_args]
[heading Header]
``#include <boost/callable_traits/replace_args.hpp>``
[heading Definition]
*/

template<std::size_t Index, typename T, typename... Args>
using replace_args_t = //implementation-defined
//<-
    // substitution failure if index is out of range or if parameter
    // types cannot be determined. Simple error messages are provided
    // in case the error occurs outside of a SFINAE context
    detail::fail_if_invalid<

        detail::sfinae_try<

            typename detail::traits<
                typename detail::parameter_index_helper<Index, T, true, false>::permissive_function
            >::template replace_args<detail::parameter_index_helper<Index, T, true, false>::index, Args...>,

            detail::fail_if<
                !detail::parameter_index_helper<Index, T, true, false>::has_parameter_list,
                cannot_replace_parameters_in_this_type>,

            detail::fail_if<
                detail::parameter_index_helper<Index, T, true, false>::is_out_of_range,
                index_out_of_range_for_parameter_list>
        >,

        cannot_replace_parameters_in_this_type>;
//->

template<std::size_t Index, typename T, typename... Args>
struct replace_args {
    using type = replace_args_t<Index, T, Args...>;
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
* `Index` must be less than the number of parameters in the parameter list of `T`

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* The aliased type is identical to `T`, except that the parameter list types are "overwritten" by `Args...`, beginning at zero-based `Index`.
* * If `sizeof...(Args)` is greater than then number of function parameters in `T` minus `Index`, the aliased type will contain more parameters than `T`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

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
