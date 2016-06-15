/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_VARARGS_HPP
#define CALLABLE_TRAITS_ADD_VARARGS_HPP

#include <callable_traits/detail/core.hpp>

//[add_varargs_hpp
//`[section:ref_add_varargs add_varargs]

namespace callable_traits {

    template<typename T>
    struct add_varargs {

        using type = //implementation-defined
        //<-
            detail::fail_if_invalid<
                typename detail::traits<T>::add_varargs,
                varargs_are_illegal_for_this_type>;
        //->
    };

    template<typename T>
    using add_varargs_t = typename add_varargs<T>::type;
}

/*`
[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer
  * function reference
  * member function pointer

[heading Behavior]
* Adds C-style variadics (`...`) to the signature of `T`, if not already present
  * `add_varargs<int()>` aliases `int(...)`
  * `add_varargs<int(*)()>` aliases `int(*)(int, ...)`
  * `add_varargs<int(&)()>` aliases `int(&)(int, ...)`
  * `add_varargs<int(foo::*)() const>` aliases `int(foo::*)(...) const`

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
