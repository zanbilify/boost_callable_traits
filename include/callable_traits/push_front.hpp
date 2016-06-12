/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_PUSH_FRONT_HPP
#define CALLABLE_TRAITS_PUSH_FRONT_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct args_push_front_error : sfinae_error {

            static_assert(Sfinae,
                "callable_traits::push_front<T, Args...> is "
                "not a meaningful operation for this T.");
        };
    }

    template<typename T, typename... Args>
    struct args_push_front {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::template push_front<Args...>,
            cannot_determine_parameters_for_this_type>;
    };

    template<typename T, typename... Args>
    using args_push_front_t =
        typename args_push_front<T, Args...>::type;
}

#endif //CALLABLE_TRAITS_PUSH_FRONT_HPP
