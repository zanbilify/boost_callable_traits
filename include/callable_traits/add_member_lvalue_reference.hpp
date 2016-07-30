/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_MEMBER_LVALUE_REFERENCE_HPP
#define CALLABLE_TRAITS_ADD_MEMBER_LVALUE_REFERENCE_HPP

#include <callable_traits/detail/core.hpp>

CALLABLE_TRAITS_NAMESPACE_BEGIN

//[ add_member_lvalue_reference_hpp
/*`
[section:ref_add_member_lvalue_reference add_member_lvalue_reference]
[heading Header]
``#include<callable_traits/add_member_lvalue_reference.hpp>``
[heading Definition]
*/

#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

template<typename T>
struct add_member_lvalue_reference_t {
    static_assert(sizeof(T) < 1,
        "Reference member qualifiers are not supported by this configuration.");
};

#else

template<typename T>
using add_member_lvalue_reference_t = //implementation-defined
//<-
#ifdef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_lvalue_reference,

        detail::fail_if<
            std::is_same<typename detail::traits<T>::add_member_lvalue_reference,
                detail::abominable_functions_not_supported_on_this_compiler>::value,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if<
            std::is_same<typename detail::traits<T>::add_member_lvalue_reference,
                detail::invalid_type>::value,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::fail_if_invalid<
        typename detail::traits<T>::add_member_lvalue_reference,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS
//->

#endif // #ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

template<typename T>
struct add_member_lvalue_reference {
    using type = add_member_lvalue_reference_t<T>;
};

//<-
CALLABLE_TRAITS_NAMESPACE_END
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member lvalue reference qualifier (`&`) to `T`, if not already present.
* If an rvalue reference qualifier is present, the lvalue reference qualifier replaces it (in accordance with reference collapsing rules).

[heading Compatibility Notes]
A `static_assert` always fails on GCC builds older than version 4.9.2, because those versions did not support reference member qualifiers. Full support on GCC 4.9.2+, Clang 3.5+, Visual Studio 2015, and XCode 6.4+.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_lvalue_reference_t<T>`]]
    [[`int()`]                          [`int() &`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() &`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() &`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const &`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() & transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_lvalue_reference.cpp]
[add_member_lvalue_reference]
[endsect]
*/
//]

#endif

