/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_PARENT_CLASS_OF_HPP
#define BOOST_CLBL_TRTS_PARENT_CLASS_OF_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ parent_class_of_hpp
/*`
[section:ref_parent_class_of parent_class_of]
[heading Header]
``#include <boost/callable_traits/parent_class_of.hpp>``
[heading Definition]
*/

template<typename T>
using parent_class_of_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::class_type,
        type_is_not_a_member_pointer>;
//->

template<typename T, typename U = parent_class_of_t<T>>
struct parent_class_of {
    using type = U;
};

//<-
BOOST_CLBL_TRTS_NAMESPACE_END
//->

/*`
[heading Constraints]
* `T` must be a member pointer

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* The aliased type is the parent class of the member. In other words, if `T` is expanded to `U C::*`, the aliased type is `C`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`parent_class_of_t<T>`]]
    [[`int foo::*`]                     [`foo`]]
    [[`void(foo::*)() const`]           [`foo`]]
]

[heading Example Program]
[import ../example/parent_class_of.cpp]
[parent_class_of]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_PARENT_CLASS_OF_HPP
