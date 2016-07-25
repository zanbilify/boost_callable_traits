/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_EXPAND_ARGS_LEFT_HPP
#define CALLABLE_TRAITS_EXPAND_ARGS_LEFT_HPP

#include <callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

//[ expand_args_left_hpp
/*`[section:ref_expand_args_left expand_args_left]
[heading Header]
``#include<callable_traits/expand_args_left.hpp>``
[heading Definition]
*/

template<typename T, template<class...> class Container, typename... RightArgs>
using expand_args_left_t = //implementation-defined
//<-
    detail::fail_if_invalid<
        typename detail::traits<T>::template
            expand_args_left<Container, RightArgs...>,
        cannot_expand_the_parameter_list_of_first_template_argument>;
//->

template<typename T, template<class...> class Container, typename... RightArgs>
struct expand_args_left {
    using type = expand_args_left_t<T, Container, RightArgs...>;
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
* `expand_args_left` is identical to `expand_args`, except that additional type arguments for `Container` may be supplied. the types determined by `T` are expanded first (on the *left*), followed by the supplied `RightArgs...`.
* If `Container` cannot be legally instantiated according to the behavior defined above with respect to `T` and `RightArgs...`, the behavior is undefined.

[/TODO is this needed?
* When `T` is a function, function pointer, or function reference, the aliased type is an instantiation of the `Container` template, where the first types passed to the template are the parameter list types of `T`, and the subsequent type arguments are the supplied `RightArgs...`
* When `T` is a function object, the aliased type is an instantiation of the `Container` template, where the first types passed to the template are the parameter list types of `T`'s `operator()`, and the subsequent type arguments are the supplied `RightArgs...`
* When `T` is a member function pointer, the aliased type is a `Container` template instantiation, where the first template type argument is a reference to the parent class of `T`, qualified according to the member qualifiers on `T`, such that this type is equivalent to `callable_traits::qualified_parent_class_of_t<T>`. The next type arguments passed to the `Container` template are the parameter list types of the member function. The supplied `RightArgs...` are passed as the right-most types in the template type argument list.
* When `T` is a member data pointer, the aliased type is the `Container` template instantiated with a const reference to parent class of `T`, followed by the supplied `RightArgs...`.]

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

#endif //CALLABLE_TRAITS_EXPAND_ARGS_LEFT_HPP
