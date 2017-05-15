/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_reference_hpp
/*`
[section:ref_remove_member_reference remove_member_reference]
[heading Header]
``#include <boost/callable_traits/remove_member_reference.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_reference_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_reference,
        member_qualifiers_are_illegal_for_this_type>;
//->

template<typename T, typename U = remove_member_reference_t<T>>
struct remove_member_reference {
    using type = U;
};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type

[heading Behavior]
* A substitution failure occuers if the constraints are violated.
* Removes member `&` or `&&` qualifiers from `T`, if present.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_const_t<T>`]]
    [[`int() &`]                        [`int()`]]
    [[`int(foo::*)() &`]                [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() const`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() const`]]
    [[`int(foo::*)()`]                  [`int(foo::*)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_reference.cpp]
[remove_member_reference]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP
