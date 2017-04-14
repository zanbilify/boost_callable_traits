/*

@copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_RESULT_OF_HPP
#define BOOST_CLBL_TRTS_RESULT_OF_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(return_type)
BOOST_CLBL_TRTS_SFINAE_MSG(return_type, unable_to_determine_return_type)

//[ return_type_hpp
/*`
[section:ref_return_type return_type]
[heading Header]
``#include <boost/callable_traits/return_type.hpp>``
[heading Definition]
*/

template<typename T>
using return_type_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::return_type,
        unable_to_determine_return_type>;
//->

template<typename T>
struct return_type {
    using type = return_type_t<T>;
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
  * member data pointer
  * user-defined type with a non-overloaded `operator()`
  * type of a non-generic lambda

[heading Behavior]
* When the constraints are violated, a substitution failure occurs.
* The aliased type is the return type of `T`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`return_type_t<T, std::tuple>`]]
    [[`void()`]                         [`void`]]
    [[`float(*)()`]                     [`float`]]
    [[`const char*(&)()`]               [`const char *`]]
    [[`int(foo::*)() const`]            [`int`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/return_type.cpp]
[return_type]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_RESULT_OF_HPP
