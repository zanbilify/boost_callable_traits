/*

@copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_RESULT_OF_HPP
#define CALLABLE_TRAITS_RESULT_OF_HPP

#include <callable_traits/detail/core.hpp>

//[ return_type_hpp
/*`
[section:ref_return_type return_type]
[heading Header]
``#include<callable_traits/return_type.hpp>``
[heading Definition]
*/

CALLABLE_TRAITS_NAMESPACE_BEGIN

    template<typename T>
    using return_type_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::return_type,
            unable_to_determine_return_type>;
    //->

    template<typename T>
    struct return_type {
        using type = return_type_t<T>;
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
  * user-defined type with a non-overloaded `operator()`
  * type of a non-generic lambda

[heading Behavior]
* When the constraints are violated, a substitution failure occurs.
* The aliased type is the return type of `T`.

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

#endif //#ifndef CALLABLE_TRAITS_RESULT_OF_HPP
