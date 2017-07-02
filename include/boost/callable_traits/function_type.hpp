/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_FUNCTION_TYPE_HPP
#define BOOST_CLBL_TRTS_FUNCTION_TYPE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ function_type_hpp
/*`[section:ref_function_type function_type]
[heading Header]
``#include <boost/callable_traits/function_type.hpp>``
[heading Definition]
*/

template<typename T>
using function_type_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::function_type,
        cannot_determine_parameters_for_this_type>;
//->

template<typename T, typename U = function_type_t<T>>
struct function_type {
    using type = U;
};

//<-
}} // namespace boost::callable_traits
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
* When `T` is a function, the aliased type is identical to `T`, except that the aliased function type will not have member qualifiers or the `transaction_safe` specifier.
* When `T` is a function pointer, the aliased type is equivalent to `std::remove_pointer_t<T>`.
* When `T` is a function reference, the aliased type is equivalent to `std::remove_reference_t<T>`.
* When `T` is a function object, the aliased type is a function type with the same return type and parameter list as `T`'s `operator()`.
* When `T` is a member function pointer, the aliased type is a function type with the same return type as `T`, and the first parameter is a reference to the parent class of `T`, qualified according to the member qualifiers on `T`. The subsequent parameters, if any, are the parameter types of `T`.
* When `T` is a member data pointer, the aliased type is a function type returning the underlying member type of `T`, taking a single parameter, which is a `const` reference to the parent type of `T`.
* In all cases, the aliased function type will not have member qualifiers, and will not have the `transaction_safe` specifier.

[heading Input/Output Examples]
[table
    [[`T`]                              [`function_type_t<T>`]]
    [[`void(int)`]                      [`void(int)`]]
    [[`void(int) const`]                [`void(int)`]]
    [[`void(int) transaction_safe`]     [`void(int)`]]
    [[`void(*)(int)`]                   [`void(int)`]]
    [[`void(&)(int)`]                   [`void(int)`]]
    [[`void(*)()`]                      [`void()`]]
    [[`int(foo::*)(int)`]               [`int(foo&, int)`]]
    [[`int(foo::*)(int) const`]         [`int(const foo&, int)`]]
    [[`void(foo::*)() volatile &&`]     [`void(volatile foo&&)`]]
    [[`int foo::*`]                     [`int(const foo&)`]]
    [[`const int foo::*`]               [`int(const foo&)`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[import ../example/function_type.cpp]
[function_type]
[endsect]
*/
//]

#endif
