/*!
@file remove_transaction_safe

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_TRANSACTION_SAFE_HPP
#define CALLABLE_TRAITS_REMOVE_TRANSACTION_SAFE_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(remove_transaction_safe)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(remove_transaction_safe,
        cannot_remove_transaction_safe_from_this_type)

    template<typename T>
    struct remove_transaction_safe {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::remove_transaction_safe,
            cannot_remove_transaction_safe_from_this_type>;
    };

    template<typename T>
    using remove_transaction_safe_t =
        typename remove_transaction_safe<T>::type;
}

#endif //#ifndef CALLABLE_TRAITS_REMOVE_TRANSACTION_SAFE_HPP
