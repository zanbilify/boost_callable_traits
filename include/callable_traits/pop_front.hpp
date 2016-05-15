/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_POP_FRONT_HPP
#define CALLABLE_TRAITS_POP_FRONT_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct pop_front_error {

            static_assert(Sfinae,
                "callable_traits::push_back<T, Args...> is "
                "not a meaningful operation for this T.");
        };
    }

    template<typename T, std::size_t Count = 1>
    using pop_front = detail::fail_if_invalid<
        typename detail::traits<T>::template pop_front<Count>,
        detail::pop_front_error<true>>;
}

#endif //CALLABLE_TRAITS_POP_BACK_HPP
