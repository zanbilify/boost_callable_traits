/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARG_AT_HPP
#define CALLABLE_TRAITS_ARG_AT_HPP

#include <callable_traits/args.hpp>
#include <callable_traits/detail/core.hpp>
#include <tuple>

//[ arg_at_hpp
//`[section:ref_arg_at arg_at]

namespace callable_traits {

    template<std::size_t I, typename T>
    struct arg_at {
        //<-
        private:

            using arg_types = typename args<T>::type;

        public:
        //->

        using type = //implementation-defined

        //<-
        // substitution failure if index is out of range or if argument
        // types cannot be determined. Simple error messages are provided
        // in case the error occurs outside of a SFINAE context
            detail::sfinae_try<

                detail::at<I, arg_types>,

                detail::fail_if<I >= std::tuple_size<arg_types>::value,
                    index_out_of_range_for_parameter_list>
            >;
        //->
    };

    template<std::size_t I, typename T>
    using arg_at_t = typename arg_at<I, T>::type;
}

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
* If any constraints are violated, a substitution failure occurs
* Otherwise, `arg_at<Index, T>` aliases `std::tuple_element_t<Index, `[namespace_scoped][link_args]`<T>>`, such that:
  * `arg_at<0, void(char, short, long, int*)>` aliases `char`
  * `arg_at<1, void(*)(char, short, long, int*)>` aliases `short`
  * `arg_at<2, void(&)(char, short, long, int*)>` aliases `long`

[heading Example]
[/import ../example/arg_at.cpp]
[arg_at]
[endsect]
*/
//]
#endif
