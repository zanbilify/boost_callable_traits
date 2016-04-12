/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARG_AT_HPP
#define CALLABLE_TRAITS_ARG_AT_HPP

#include <callable_traits/args.hpp>
#include <callable_traits/detail/required_definitions.hpp>
#include <tuple>

namespace callable_traits {
	
    namespace detail {
        struct arg_at_error{};
    }

    namespace permissive {

        // returns callable_traits::invalid_type if
        // index is out of range
        template<size_t I, typename T>
        using arg_at = detail::weak_at<I,
            detail::fallback_if_invalid<
                permissive::args<T>, std::tuple<>>>;
    }

    namespace verbose {

        // Letting the static_assert in std::tuple_element
        // handle the error message here.
        template<size_t I, typename T>
        using arg_at = typename std::tuple_element<I, args<T>>::type;
    }

    template<size_t I, typename T>
    using arg_at = detail::fail_if_invalid<
        permissive::arg_at<I, T>,
        detail::arg_at_error>;
}

#endif
