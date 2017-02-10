/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_EXPAND_ARGS_HPP
#define CALLABLE_TRAITS_EXPAND_ARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

//[ expand_args_hpp
/*`[section:ref_expand_args expand_args]
[heading Header]
``#include <boost/callable_traits/expand_args.hpp>``
[heading Definition]
*/

template<typename T, template<class...> class Container>
using expand_args_t = //implementation-defined
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::template expand_args<Container>,
        cannot_expand_the_parameter_list_of_first_template_argument>;
//->

template<typename T, template<class...> class Container>
struct expand_args {
    using type = expand_args_t<T, Container>;
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
* When `T` is a function, function pointer, or function reference, the aliased type is the `Container` template instantiated with the types from the parameter list of `T`.
* When `T` is a function object, the aliased type is the `Container` template instantiated with the types from the parameter list of `T`'s `operator()`.
* When `T` is a member function pointer, the aliased type is a `Container` template instantiation, where the first template type argument is a reference to the parent class of `T`, qualified according to the member qualifiers on `T`, such that this type is equivalent to `boost::callable_traits::qualified_parent_class_of_t<T>`. The subsequent template type arguments are the parameter list of the member function.
* When `T` is a member data pointer, the aliased type is the `Container` template instantiated with a `const` reference to the parent class of `T`.
* If `Container` cannot be legally instantiated according to the behavior defined above with respect to `T`, the behavior is undefined.

[heading Compatibility Notes]
Full support on GCC 4.7.4+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`expand_args_t<T, std::tuple>`]]
    [[`void(float, char, int)`]         [`std::tuple<float, char, int>`]]
    [[`void(*)(float, char, int)`]      [`std::tuple<float, char, int>`]]
    [[`void(&)(float, char, int)`]      [`std::tuple<float, char, int>`]]
    [[`void(float, char, int) const &&`][`std::tuple<float, char, int>`]]
    [[`void(*)()`]                      [`std::tuple<>`]]
    [[`void(*)() transaction_safe`]     [`std::tuple<>`]]
    [[`void(foo::*)(float, char, int)`] [`std::tuple<foo&, float, char, int>`]]
    [[`int(foo::*)(int) const`]         [`std::tuple<const foo&, float, char, int>`]]
    [[`void(foo::*)() volatile &&`]     [`std::tuple<volatile foo &&>`]]
    [[`int foo::*`]                     [`std::tuple<const foo&>`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/expand_args.cpp]
[expand_args]
[endsect]
*/
//]

#endif //CALLABLE_TRAITS_EXPAND_ARGS_HPP
