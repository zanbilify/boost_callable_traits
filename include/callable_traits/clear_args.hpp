/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CLEAR_ARGS_HPP
#define CALLABLE_TRAITS_CLEAR_ARGS_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(clear_args)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(clear_args,
        cannot_clear_the_parameter_list_for_this_type)

    template<typename T>
    struct clear_args {

        using type = detail::fail_if_invalid<
        typename detail::traits<T>::clear_args,
        cannot_clear_the_parameter_list_for_this_type>;
    };

    template<typename T>
    using clear_args_t = typename clear_args<T>::type;
}

#endif //CALLABLE_TRAITS_CLEAR_ARGS_HPP
