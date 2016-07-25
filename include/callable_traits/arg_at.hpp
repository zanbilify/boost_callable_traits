/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARG_AT_HPP
#define CALLABLE_TRAITS_ARG_AT_HPP

#include <callable_traits/detail/core.hpp>
#include <callable_traits/detail/parameter_index_helper.hpp>
#include <tuple>

//[ arg_at_hpp
/*`[section:ref_arg_at arg_at]
[heading Header]
``#include<callable_traits/arg_at.hpp>``
[heading Definition]
*/

CALLABLE_TRAITS_NAMESPACE_BEGIN



template<std::size_t I, typename T>
using arg_at_t = //implementation-defined
//<-
// substitution failure if index is out of range or if argument
// types cannot be determined. Simple error messages are provided
// in case the error occurs outside of a SFINAE context
    detail::sfinae_try<

        typename std::tuple_element<
            detail::parameter_index_helper<I, T>::index,
            typename detail::parameter_index_helper<I,T>::permissive_tuple
        >::type,

        detail::fail_if<
            !detail::parameter_index_helper<I, T>::has_parameter_list,
            cannot_determine_parameters_for_this_type>,

        detail::fail_if<
            detail::parameter_index_helper<I, T>::is_out_of_range,
            index_out_of_range_for_parameter_list>
    >;
//->

template<std::size_t I, typename T>
struct arg_at {
    using type = arg_at_t<I, T>;
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
  * member data pointer
  * user-defined type with non-overloaded `operator()`
  * type of a non-generic lambda
* `I` must be less than `std::tuple_size<callable_traits::args_t<T>>::value`

[heading Behavior]
* If any constraints are violated, a substitution failure occurs.
* Otherwise, `arg_at_t<Index, T>` is equivalent to `std::tuple_element_t<Index, callable_traits::args_t<T>>`.

[heading Example Program]
[/import ../example/arg_at.cpp]
[arg_at]
[endsect]
*/
//]
#endif
