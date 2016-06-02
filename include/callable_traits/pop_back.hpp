/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_POP_BACK_HPP
#define CALLABLE_TRAITS_POP_BACK_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct args_pop_back_error : sfinae_error {

            static_assert(Sfinae,
                "callable_traits::args_push_back<T, Args...> is "
                "not a meaningful operation for this T.");
        };
    }

    template<typename T, std::size_t Count = 1>
    struct args_pop_back {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::template pop_back<Count>,
            detail::args_pop_back_error<true>>;
    };

    template<typename T, std::size_t Count = 1>
    using args_pop_back_t =
        typename args_pop_back<T, Count>::type;
}

#endif //CALLABLE_TRAITS_POP_BACK_HPP
