/*

@copyright Barrett Adair 2015

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP
#define BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ remove_varargs_hpp
/*`
[section:ref_remove_varargs remove_varargs]
[heading Header]
``#include <boost/callable_traits/remove_varargs.hpp>``
[heading Definition]
*/

template<typename T>
using remove_varargs_t = //implementation-defined
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_varargs,
        varargs_are_illegal_for_this_type>;
//->

template<typename T>
struct remove_varargs {
    using type = remove_varargs_t<T>;
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
* Removes C-style variadics (`...`) from the signature of `T`, if present.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

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
