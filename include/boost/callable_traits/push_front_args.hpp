/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_PUSH_FRONT_ARGS_HPP
#define BOOST_CLBL_TRTS_PUSH_FRONT_ARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ push_front_args_hpp
/*`
[section:ref_push_front_args push_front_args]
[heading Header]
``#include <boost/callable_traits/push_front_args.hpp>``
[heading Definition]
*/

template<typename T, typename... Args>
using push_front_args_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::template push_front<Args...>,
        cannot_determine_parameters_for_this_type>;
//->

template<typename T, typename... Args>
struct push_front_args {
    using type = push_front_args_t<T, Args...>;
};

//<-
BOOST_CLBL_TRTS_NAMESPACE_END
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
* The aliased type is identical to `T`, except that `Args...` types have been added to the front of the parameter list.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

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

#endif //BOOST_CLBL_TRTS_PUSH_FRONT_ARGS_HPP
