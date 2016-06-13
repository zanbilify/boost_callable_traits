/*!
@file add_transaction_safe

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_TRANSACTION_SAFE_HPP
#define CALLABLE_TRAITS_ADD_TRANSACTION_SAFE_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(add_transaction_safe)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(add_transaction_safe,
        cannot_add_transaction_safe_to_this_type)

    template<typename T>
    struct add_transaction_safe {

        using type =

#ifdef CALLABLE_TRAITS_ENABLE_TRANSACTION_SAFE

            detail::fail_if_invalid<
                typename detail::traits<T>::add_transaction_safe,
                cannot_add_transaction_safe_to_this_type>;
#else

            detail::sfinae_try<T,
                detail::fail_if<true,
                    transaction_safe_is_not_enabled_on_this_platform>>;
#endif

    };


    template<typename T>
    using add_transaction_safe_t =
        typename add_transaction_safe<T>::type;
}

#endif //#ifndef CALLABLE_TRAITS_ADD_TRANSACTION_SAFE_HPP
