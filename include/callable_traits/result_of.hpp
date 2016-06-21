/*

@copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_RESULT_OF_HPP
#define CALLABLE_TRAITS_RESULT_OF_HPP

#include <callable_traits/detail/core.hpp>

//[ result_of_hpp
/*`
[section:ref_result_of result_of]
[heading Header]
``#include<callable_traits/result_of.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T>
    using result_of_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::return_type,
            unable_to_determine_return_type>;
    //->

    template<typename T>
    struct result_of {
        using type = result_of_t<T>;
    };
}

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
    [[`T`]                              [`result_of_t<T, std::tuple>`]]
    [[`void()`]                         [`void`]]
    [[`float(*)()`]                     [`float`]]
    [[`const char*(&)()`]               [`const char *`]]
    [[`int(foo::*)() const`]            [`int`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/result_of.cpp]
[result_of]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_RESULT_OF_HPP
