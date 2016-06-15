/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_APPLY_RETURN_HPP
#define CALLABLE_TRAITS_APPLY_RETURN_HPP

#include <callable_traits/detail/core.hpp>

//[ apply_return_hpp
//`[section:ref_apply_return apply_return]

namespace callable_traits {
    //<-
    namespace detail {

        template<typename T, typename R>
        struct apply_return_helper {
            using type = typename detail::traits<T>::template apply_return<R>;
        };

        //special case
        template<typename... Args, typename R>
        struct apply_return_helper<std::tuple<Args...>, R> {
            using type = R(Args...);
        };
    }

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(apply_return)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(apply_return,
    invalid_types_for_apply_return)
    //->

    template<typename T, typename R>
    struct apply_return {

        using type = //implementation-defined
        //<-
            detail::fail_if_invalid<
                typename detail::apply_return_helper<T, R>::type,
                invalid_types_for_apply_return>;
        //->
    };

    template<typename T, typename R>
    using apply_return_t = typename apply_return<T, R>::type;
}

/*`
[heading Constraints]
* `T` must one of the following:
  * `std::tuple` template instantiation
  * function
  * function pointer
  * function reference
  * member function pointer
  * member data pointer

[heading Behavior]
* When `T` is `std::tuple<Args...>`, the aliased type is `R(Args...)`
* When `T` is a function, function pointer, function reference, or member function pointer, the aliased type's return type is `R`, but is otherwise identical to `T`
* When `T` is a member data pointer of class `foo` to a `U` type (such that `T` is `U foo::*`), the aliased type is `R foo::*`

[heading Input/Output Examples]
[table
    [[`T`]                              [`apply_return_t<T, float>`]]
    [[`std::tuple<int, int>`]           [`float(int, int)`]]
    [[`int()`]                          [`float()`]]
    [[`int (&)()`]                      [`float(&)()`]]
    [[`int (*)()`]                      [`float(*)()`]]
    [[`int (*)(...)`]                   [`float(*)()`]]
    [[`int(foo::*)()`]                  [`float(foo::*)()`]]
    [[`int(foo::*)() &`]                [`float(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`float(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`float(foo::*)() const`]]
    [[`int(foo::*)() transaction_safe`] [`float(foo::*)() transaction_safe`]]
    [[`int foo::*`]                     [`float foo::*`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[/import ../example/apply_return.cpp]
[apply_return]
[endsect]
*/
//]
#endif
