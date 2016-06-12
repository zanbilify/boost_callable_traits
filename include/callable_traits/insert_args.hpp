/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_INSERT_ARGS_HPP
#define CALLABLE_TRAITS_INSERT_ARGS_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<std::size_t Index, typename T, typename... Args>
    struct insert_args {
        using type = detail::fail_if_invalid<
            typename detail::traits<T>::template insert_args<Index, Args...>,
            cannot_determine_parameters_for_this_type>;
    };

    template<std::size_t Index, typename T, typename... Args>
    using insert_args_t =
        typename insert_args<Index, T, Args...>::type;
}

#endif //CALLABLE_TRAITS_INSERT_ARGS_HPP
