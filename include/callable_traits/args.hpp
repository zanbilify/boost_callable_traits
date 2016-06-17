/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARGS_HPP
#define CALLABLE_TRAITS_ARGS_HPP

#include <callable_traits/detail/core.hpp>

//[ args_hpp
/*`[section:ref_args args]
[heading Header]
``#include<callable_traits/args.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T>
    using args_t = //implementation-defined
    //<-
        detail::fail_if_invalid<
            typename detail::traits<T>::arg_types,
            cannot_determine_parameters_for_this_type>;
    //->

    template<typename T>
    struct args {
        using type = args_t<T>;
    };
}

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
* When `T` is a function, function pointer, or function reference, the aliased type is a `std::tuple` whose element types match those of the function's parameter list.
* When `T` is a function object, the aliased type is a `std::tuple` whose element types match those of the function object's `operator()` parameter list.
* When `T` is a member function pointer, the aliased type is a `std::tuple` instantiation, where the first tuple element is a reference to the parent class of `T`, qualified according to the member qualifiers on `T`, such that this first tuple element type is equivalent to `callable_traits::qualified_parent_class_of<T>`. The subsequent template type arguments, if any, are the parameter types of the member function.
* When `T` is a member data pointer, the aliased type is a `std::tuple` with a single element, which is a `const` reference to the parent type of the member.

[heading Input/Output Examples]
[table
    [[`T`]                              [`args_t<T>`]]
    [[`void(float, char, int)`]         [`std::tuple<float, char, int>`]]
    [[`void(*)(float, char, int)`]      [`std::tuple<float, char, int`]]
    [[`void(&)(float, char, int)`]      [`std::tuple<float, char, int`]]
    [[`void(float, char, int) const &&`][`std::tuple<float, char, int>`]]
    [[`void(*)()`]                      [`std::tuple<>`]]
    [[`void(foo::*)(float, char, int)`] [`std::tuple<foo&, float, char, int>`]]
    [[`int(foo::*)(int) const`]         [`std::tuple<const foo&, int>`]]
    [[`void(foo::*)() volatile &&`]     [`std::tuple<volatile foo &&>`]]
    [[`int foo::*`]                     [`std::tuple<const foo&>`]]
    [[`const int foo::*`]               [`std::tuple<const foo&>`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/args.cpp]
[args]
[endsect]
*/
//]

#endif //#ifndef CALLABLE_TRAITS_ARGS_HPP
