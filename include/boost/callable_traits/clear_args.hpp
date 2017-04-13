/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_CLEAR_ARGS_HPP
#define BOOST_CLBL_TRTS_CLEAR_ARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(clear_args)
BOOST_CLBL_TRTS_SFINAE_MSG(clear_args, cannot_clear_the_parameter_list_of_this_type)

//[ clear_args_hpp
/*`[section:ref_clear_args clear_args]
[heading Header]
``#include <boost/callable_traits/clear_args.hpp>``
[heading Definition]
*/

template<typename T>
using clear_args_t = //implementation-defined
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::clear_args,
        cannot_clear_the_parameter_list_of_this_type>;
//->

template<typename T>
struct clear_args {
    using type = clear_args_t<T>;
};

//<-
BOOST_CLBL_TRTS_NAMESPACE_END
//->

/*`
[heading Constraints]
* `T` must be one of the following:
  * function
  * function pointer
  * function reference
  * member function pointer

[heading Behavior]
* When the constraints are violated, a substitution failure occurs.
* The aliased type has an empty parameter list, but is otherwise identical to `T`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`clear_args_t<T>`]]
    [[`void(float, char, int)`]         [`void()`]]
    [[`void(*)(float, char, int)`]      [`void(*)()`]]
    [[`void(&)(float, char, int)`]      [`void(&)()`]]
    [[`void(float, char, int) const &&`][`void() const &&`]]
    [[`void(*)()`]                      [`void(*)()`]]
    [[`void(foo::*)(float, char, int)`] [`void(foo::*)()`]]
    [[`int(foo::*)(int) const`]         [`int(foo::*)() const`]]
    [[`void(foo::*)() volatile &&`]     [`void(foo::*)() volatile &&`]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/clear_args.cpp]
[clear_args]
[endsect]
*/
//]

#endif //BOOST_CLBL_TRTS_CLEAR_ARGS_HPP
