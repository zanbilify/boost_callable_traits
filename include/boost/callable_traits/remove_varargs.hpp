/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP
#define BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_varargs_hpp
/*`
[section:ref_remove_varargs remove_varargs]
[heading Header]
``#include <boost/callable_traits/remove_varargs.hpp>``
[heading Definition]
*/

template<typename T>
using remove_varargs_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_varargs,
        varargs_are_illegal_for_this_type>;
//->

template<typename T, typename U = remove_varargs_t<T>>
struct remove_varargs {
    using type = U;
};

//<-
}} // namespace boost::callable_traits
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
* Removes C-style variadics (`...`) from the signature of `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                                 [`remove_varargs_t<T>`]]
    [[`int(...)`]                          [`int()`]]
    [[`int(int, ...)`]                     [`int(int)`]]
    [[`int (&)(...)`]                      [`int(&)()`]]
    [[`int (*)()`]                         [`int(*)()`]]
    [[`int(foo::*)(...)`]                  [`int(foo::*)()`]]
    [[`int(foo::*)(...) &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)(...) &&`]               [`int(foo::*)() &&`]]
    [[`int(foo::*)(...) const`]            [`int(foo::*)() const`]]
    [[`int(foo::*)(...) transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int`]                               [(substitution failure)]]
    [[`int foo::*`]                        [(substitution failure)]]
    [[`int (* const)()`]                   [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_varargs.cpp]
[remove_varargs]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP
