/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_INSERT_ARGS_HPP
#define BOOST_CLBL_TRTS_INSERT_ARGS_HPP

#include <boost/callable_traits/detail/core.hpp>
#include <boost/callable_traits/detail/parameter_index_helper.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(insert_args)
BOOST_CLBL_TRTS_SFINAE_MSG(insert_args, cannot_insert_parameters_into_this_type)

//[ insert_args_hpp
/*`[section:ref_insert_args insert_args]
[heading Header]
``#include <boost/callable_traits/insert_args.hpp>``
[heading Definition]
*/

template<std::size_t Index, typename T, typename... Args>
using insert_args_t = //see below
//<-
    // substitution failure if index is out of range or if parameter
    // types cannot be determined. Simple error messages are provided
    // in case the error occurs outside of a SFINAE context
    detail::try_but_fail_if_invalid<

        detail::sfinae_try<

            typename detail::traits<
                typename detail::parameter_index_helper<Index, T, true, true>::permissive_function
            >::template insert_args<detail::parameter_index_helper<Index, T, true, true>::index, Args...>,

            detail::fail_if<
                !detail::parameter_index_helper<Index, T, true, true>::has_parameter_list,
                typename std::conditional<std::is_reference<T>::value,
                    reference_type_not_supported_by_this_metafunction,
                    cannot_insert_parameters_into_this_type>::type>,

            detail::fail_if<
                detail::parameter_index_helper<Index, T, true, true>::is_out_of_range,
                index_out_of_range_for_parameter_list>
        >,

        cannot_insert_parameters_into_this_type>;
//->

template<std::size_t Index, typename T, typename... Args>
struct insert_args {
    using type = insert_args_t<Index, T, Args...>;
};

//<-
}} // namespace boost::callable_traits
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

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

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

#endif //BOOST_CLBL_TRTS_INSERT_ARGS_HPP
