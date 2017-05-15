/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_VARARGS_HPP
#define BOOST_CLBL_TRTS_ADD_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_varargs_hpp
/*`
[section:ref_add_varargs add_varargs]
[heading Header]
``#include <boost/callable_traits/add_varargs.hpp>``
[heading Definition]
*/

template<typename T>
using add_varargs_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_varargs,
        varargs_are_illegal_for_this_type>;
//->

template<typename T, typename U = add_varargs_t<T>>
struct add_varargs {
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
* Adds C-style variadics (`...`) to the signature of `T`, if not already present.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_varargs_t<T>`]]
    [[`int()`]                          [`int(...)`]]
    [[`int(int)`]                          [`int(int, ...)`]]
    [[`int (&)()`]                      [`int(&)(...)`]]
    [[`int (*)()`]                      [`int(*)(...)`]]
    [[`int (*)(...)`]                   [`int(*)(...)`]]
    [[`int(foo::*)()`]                  [`int(foo::*)(...)`]]
    [[`int(foo::*)() &`]                [`int(foo::*)(...) &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)(...) &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)(...) const`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)(...) transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (*&)()`]                     [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_varargs.cpp]
[add_varargs]
[endsect]
*/
//]

#endif
