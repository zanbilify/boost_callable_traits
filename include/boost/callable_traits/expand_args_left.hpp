/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_EXPAND_ARGS_LEFT_HPP
#define BOOST_CLBL_TRTS_EXPAND_ARGS_LEFT_HPP

#include <boost/callable_traits/detail/core.hpp>

BOOST_CLBL_TRTS_NAMESPACE_BEGIN

//[ expand_args_left_hpp
/*`[section:ref_expand_args_left expand_args_left]
[heading Header]
``#include <boost/callable_traits/expand_args_left.hpp>``
[heading Definition]
*/

template<typename T, template<class...> class Container, typename... RightArgs>
using expand_args_left_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::template
            expand_args_left<Container, RightArgs...>,
        cannot_expand_the_parameter_list_of_first_template_argument>;
//->

template<typename T, template<class...> class Container, typename... RightArgs>
struct expand_args_left {
    using type = expand_args_left_t<T, Container, RightArgs...>;
};

//<-
BOOST_CLBL_TRTS_NAMESPACE_END
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
* `expand_args_left` is identical to `expand_args`, except that additional type arguments for `Container` may be supplied. the types determined by `T` are expanded first (on the *left*), followed by the supplied `RightArgs...`.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`expand_args_left_t<T, std::tuple, short, void*>`]]
    [[`void(float, char, int)`]         [`std::tuple<float, char, int, short, void*>`]]
    [[`void(*)(float, char, int)`]      [`std::tuple<float, char, int, short, void*>`]]
    [[`void(&)(float, char, int)`]      [`std::tuple<float, char, int, short, void*>`]]
    [[`void(float, char, int) const &&`][`std::tuple<float, char, int, short, void*>`]]
    [[`void(*)()`]                      [`std::tuple<short, void*>`]]
    [[`void(*)() transaction_safe`]     [`std::tuple<short, void*>`]]
    [[`void(foo::*)(float, char, int)`] [`std::tuple<foo&, float, char, int, short, void*>`]]
    [[`int(foo::*)(int) const`]         [`std::tuple<const foo&, float, char, int, short, void*>`]]
    [[`void(foo::*)() volatile &&`]     [`std::tuple<volatile foo &&, short, void*>`]]
    [[`int foo::*`]                     [`std::tuple<const foo&, short, void*>`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/expand_args_left.cpp]
[expand_args_left]
[endsect]
*/
//]

#endif //BOOST_CLBL_TRTS_EXPAND_ARGS_LEFT_HPP
