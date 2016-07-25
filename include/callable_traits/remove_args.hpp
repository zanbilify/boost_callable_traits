/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_ARGS_HPP
#define CALLABLE_TRAITS_REMOVE_ARGS_HPP

#include <callable_traits/detail/core.hpp>
#include <callable_traits/detail/parameter_index_helper.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(remove_args)
CALLABLE_TRAITS_SFINAE_MSG(remove_args, cannot_remove_parameters_from_this_type)
CALLABLE_TRAITS_SFINAE_MSG(remove_args, parameter_list_too_short_to_remove_this_many_parameters)

//[ remove_args_hpp
/*`
[section:ref_remove_args remove_args]
[heading Header]
``#include<callable_traits/remove_args.hpp>``
[heading Definition]
*/

template<std::size_t Index, typename T, std::size_t Count = 1>
using remove_args_t = //implementation-defined
//<-
    // substitution failure if index is out of range or if parameter
    // types cannot be determined. Simple error messages are provided
    // in case the error occurs outside of a SFINAE context
    detail::fail_if_invalid<

        detail::sfinae_try<

            typename detail::traits<
                typename detail::parameter_index_helper<Index, T, true, false, Count>::permissive_function
            >::template remove_args<
                detail::parameter_index_helper<Index, T, true, false, Count>::index,
                detail::parameter_index_helper<Index, T, true, false, Count>::count>,

            detail::fail_if<
                !detail::parameter_index_helper<Index, T, true, false, Count>::has_parameter_list,
                cannot_remove_parameters_from_this_type>,

            detail::fail_if<
                detail::parameter_index_helper<Index, T, true, false, Count>::is_out_of_range,
                index_out_of_range_for_parameter_list>,

            detail::fail_if<
                (Index + Count > detail::parameter_index_helper<Index, T, true, false, Count>::parameter_list_size),
                parameter_list_too_short_to_remove_this_many_parameters>
        >,

        cannot_remove_parameters_from_this_type>;
//->

template<std::size_t Index, typename T, std::size_t Count = 1>
struct remove_args {
    using type = remove_args_t<Index, T, Count>;
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
