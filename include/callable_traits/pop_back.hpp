/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_POP_BACK_HPP
#define CALLABLE_TRAITS_POP_BACK_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct pop_back_error {

            static_assert(Sfinae,
                "callable_traits::push_back<T, Args...> is "
                "not a meaningful operation for this T.");
        };
    }

    namespace permissive {

        template<typename T, std::size_t Count = 0>
        using pop_back = detail::fallback_if_invalid<
            typename detail::traits<T>::template pop_back<Count>, T>;
    }

    namespace verbose {

        template<typename T, std::size_t Count = 0>
        using pop_back = detail::fail_if_invalid<
            typename detail::traits<T>::template pop_back<Count>,
            detail::pop_back_error<false>>;
    }

    template<typename T, std::size_t Count = 0>
    using pop_back = detail::fail_if_invalid<
        typename detail::traits<T>::template pop_back<Count>,
        detail::pop_back_error<true>>;
}

#endif //CALLABLE_TRAITS_POP_BACK_HPP
