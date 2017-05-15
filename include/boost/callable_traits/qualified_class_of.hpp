/*

@copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP
#define BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ qualified_class_of_hpp
/*`
[section:ref_qualified_class_of qualified_class_of]
[heading Header]
``#include <boost/callable_traits/qualified_class_of.hpp>``
[heading Definition]
*/

template<typename T>
using qualified_class_of_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::invoke_type,
        type_is_not_a_member_pointer>;
//->

template<typename T, typename U = qualified_class_of_t<T>>
struct qualified_class_of {
    using type = U;
};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a member pointer

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* If `T` is a member function pointer, the aliased type is the parent class of the member, qualified according to the member qualifiers on `T`. If `T` does not have a member reference qualifier, then the aliased type will be an lvalue reference.
* If `T` is a member data pointer, the aliased type is equivalent to `ct::class_of<T> const &`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`qualified_class_of_t<T>`]]
    [[`void(foo::*)()`]                 [`foo &`]]
    [[`void(foo::*)() const`]           [`foo const &`]]
    [[`void(foo::*)() &&`]              [`foo &&`]]
    [[`void(foo::*)() volatile &&`]     [`foo volatile &&`]]
    [[`int foo::*`]                     [`foo const &`]]
    [[`const int foo::*`]               [`foo const &`]]
]

[heading Example Program]
[import ../example/qualified_class_of.cpp]
[qualified_class_of]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP
