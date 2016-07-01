/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_HAS_VARARGS_HPP
#define CALLABLE_TRAITS_HAS_VARARGS_HPP

#include <callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

//[ has_varargs_hpp
/*`[section:ref_has_varargs has_varargs]
[heading Header]
``#include<callable_traits/has_varargs.hpp>``
[heading Definition]
*/


    template<typename T>
    struct has_varargs; //implementation-defined

    //<-
    template<typename T>
    struct has_varargs
        : detail::traits<T>::has_varargs {
        using type = typename detail::traits<T>::has_varargs;
    };

    #ifdef CALLABLE_TRAITS_DISABLE_VARIABLE_TEMPLATES

    template<typename T>
    struct has_varargs_v {
        static_assert(sizeof(T) < 1,
            "Variable templates not supported on this compiler.");
    };

    #else
    //->
    template<typename T>
    constexpr bool has_varargs_v = //implementation-defined
    //<-
        detail::traits<T>::has_varargs::value;

    #endif
    //->//<-
CALLABLE_TRAITS_NAMESPACE_END
//->


/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_varargs<T>` and is aliased by `typename has_varargs<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function, function pointer, or function reference where the function's parameter list includes C-style variadics.
  * `T` is a pointer to a member function with C-style variadics in the parameter list.
  * `T` is a function object with a non-overloaded `operator()`, which has C-style variadics in the parameter list of its `operator()`.
* On compilers that support variable templates, `has_varargs_v<T>` is equivalent to `has_varargs<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_varargs_v<T>`]]
    [[`void(...)`]                      [`true`]]
    [[`void(int, ...) const`]           [`true`]]
    [[`void(*)(...)`]                   [`true`]]
    [[`void(&)(...)`]                   [`true`]]
    [[`void(foo::*)(...) const`]        [`true`]]
    [[`void(*)()`]                      [`false`]]
    [[`void(*&)()`]                     [`false`]]
    [[`int`]                            [`false`]]
    [[`const int`]                      [`false`]]
    [[`int foo::*`]                     [`false`]]
]

[heading Example Program]
[import ../example/has_varargs.cpp]
[has_varargs]
[endsect]
*/
//]

#endif
