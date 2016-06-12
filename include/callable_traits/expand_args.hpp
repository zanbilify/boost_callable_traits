/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_EXPAND_ARGS_HPP
#define CALLABLE_TRAITS_EXPAND_ARGS_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(expand_args)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(expand_args,
        cannot_expand_the_parameter_list_of_first_template_argument)

    template<typename T, template<class...> class Container>
    struct expand_args {

        using type = detail::fail_if_invalid<
        typename detail::traits<T>::template expand_args<Container>,
        cannot_expand_the_parameter_list_of_first_template_argument>;
    };

    template<typename T, template<class...> class Container>
    using expand_args_t = typename expand_args<T, Container>::type;
}

#endif //CALLABLE_TRAITS_EXPAND_ARGS_HPP
