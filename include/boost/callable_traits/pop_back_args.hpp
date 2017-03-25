/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_POP_BACK_ARGS_HPP
#define BOOST_CLBL_TRTS_POP_BACK_ARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ pop_back_args_hpp
/*`
[section:ref_pop_back_args pop_back_args]
[heading Header]
``#include <boost/callable_traits/pop_back_args.hpp>``
[heading Definition]
*/

template<typename T, std::size_t Count = 1>
using pop_back_args_t = //implementation-defined
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::template pop_back<Count>,
        cannot_determine_parameters_for_this_type>;
//->

template<typename T, std::size_t Count = 1>
struct pop_back_args {
    using type = pop_back_args_t<T, Count>;
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
* The aliased type is identical to `T`, except that `Count` number of parameters are removed from the back of the parameter list.
* If `Count` is greater than or equal to the number of parameters in `T`, then the aliased type will have an empty parameter list.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`pop_back_args_t<T, 2>`]]
    [[`int(char, short, int) const &&`] [`int(char) const &&`]]
    [[`int(*)(char, short, int)`]       [`int(*)(char)`]]
    [[`int(&)(char, short, int)`]       [`int(&)(char)`]]
    [[`int(foo::*)(char, short, int)`]  [`int(foo::*)(char)`]]
]

[heading Example Program]
[import ../example/pop_back_args.cpp]
[pop_back_args]
[endsect]
*/
//]

#endif //BOOST_CLBL_TRTS_POP_BACK_ARGS_HPP
