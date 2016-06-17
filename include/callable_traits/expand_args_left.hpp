/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_EXPAND_ARGS_LEFT_HPP
#define CALLABLE_TRAITS_EXPAND_ARGS_LEFT_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T, template<class...> class Container, typename... RightArgs>
    struct expand_args_left {

        using type = detail::fail_if_invalid<
        typename detail::traits<T>::template expand_args_left<Container, RightArgs...>,
        cannot_expand_the_parameter_list_of_first_template_argument>;
    };

    template<typename T, template<class...> class Container, typename... RightArgs>
    using expand_args_left_t = typename expand_args_left<T, Container, RightArgs...>::type;
}

#endif //CALLABLE_TRAITS_EXPAND_ARGS_LEFT_HPP
