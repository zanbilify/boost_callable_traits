/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_ARGS_HPP
#define CALLABLE_TRAITS_REMOVE_ARGS_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<std::size_t Index, typename T, std::size_t Count = 1>
    struct remove_args {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::template remove_args<Index, Count>,
            cannot_determine_parameters_for_this_type>;
    };

    template<std::size_t Index, typename T, std::size_t Count = 1>
    using remove_args_t =
        typename remove_args<Index, T, Count>::type;
}

#endif //CALLABLE_TRAITS_REMOVE_ARGS_HPP
