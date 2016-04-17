/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_AT_HPP
#define CALLABLE_TRAITS_REMOVE_AT_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct remove_at_error {

            static_assert(Sfinae,
                "callable_traits::push_back<T, Args...> is "
                "not a meaningful operation for this T.");
        };
    }

    namespace permissive {

        template<std::size_t Index, typename T, std::size_t Count = 1>
        using remove_at = detail::fallback_if_invalid<
            typename detail::traits<T>::template remove_at<Index, Count>, T>;
    }

    namespace verbose {

        template<std::size_t Index, typename T, std::size_t Count = 1>
        using remove_at = detail::fail_if_invalid<
            typename detail::traits<T>::template remove_at<Index, Count>,
            detail::remove_at_error<false>>;
    }

    template<std::size_t Index, typename T, std::size_t Count = 1>
    using remove_at = detail::fail_if_invalid<
        typename detail::traits<T>::template remove_at<Index, Count>,
        detail::remove_at_error<true>>;
}

#endif //CALLABLE_TRAITS_INSERT_AT_HPP
