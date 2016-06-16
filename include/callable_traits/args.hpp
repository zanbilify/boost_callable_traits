/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARGS_HPP
#define CALLABLE_TRAITS_ARGS_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T>
    struct args {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::arg_types,
            cannot_determine_parameters_for_this_type>;
    };

    template<typename T>
    using args_t = typename args<T>::type;
}

#endif //#ifndef CALLABLE_TRAITS_ARGS_HPP
