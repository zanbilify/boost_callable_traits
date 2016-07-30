/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_EXPAND_ARGS_RIGHT_HPP
#define CALLABLE_TRAITS_EXPAND_ARGS_RIGHT_HPP

#include <callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

//[ expand_args_right_hpp
/*`[section:ref_expand_args_right expand_args_right]
[heading Header]
``#include<callable_traits/expand_args_right.hpp>``
[heading Definition]
*/

template<typename T, template<class...> class Container, typename... LeftArgs>
using expand_args_right_t = //implementation-defined
//<-
    detail::fail_if_invalid<
        typename detail::traits<T>::template
            expand_args_right<Container, LeftArgs...>,
        cannot_expand_the_parameter_list_of_first_template_argument>;
//->

template<typename T, template<class...> class Container, typename... LeftArgs>
struct expand_args_right {
    using type = expand_args_right_t<T, Container, LeftArgs...>;
};

//<-
CALLABLE_TRAITS_NAMESPACE_END
//->

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
* `expand_args_right` is identical to `expand_args`, except that additional type arguments for `Container` may be supplied, which are expanded into the `Container` template first. The types determined by `T` are expanded last (to the *right* of the supplied `LeftArgs...`).
* If `Container` cannot be legally instantiated according to the behavior defined above with respect to `T` and `LeftArgs...`, the behavior is undefined.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`expand_args_right_t<T, std::tuple, short, void*>`]]
    [[`void(float, char, int)`]         [`std::tuple<short, void*, float, char, int>`]]
    [[`void(*)(float, char, int)`]      [`std::tuple<short, void*, float, char, int>`]]
    [[`void(&)(float, char, int)`]      [`std::tuple<short, void*, float, char, int>`]]
    [[`void(float, char, int) const &&`][`std::tuple<short, void*, float, char, int>`]]
    [[`void(*)()`]                      [`std::tuple<short, void*>`]]
    [[`void(*)() transaction_safe`]     [`std::tuple<short, void*>`]]
    [[`void(foo::*)(float, char, int)`] [`std::tuple<short, void*, foo&, float, char, int>`]]
    [[`int(foo::*)(int) const`]         [`std::tuple<short, void*, const foo&, float, char, int>`]]
    [[`void(foo::*)() volatile &&`]     [`std::tuple<short, void*, volatile foo &&>`]]
    [[`int foo::*`]                     [`std::tuple<short, void*, const foo&>`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/expand_args_right.cpp]
[expand_args_right]
[endsect]
*/
//]

#endif //CALLABLE_TRAITS_EXPAND_ARGS_RIGHT_HPP
