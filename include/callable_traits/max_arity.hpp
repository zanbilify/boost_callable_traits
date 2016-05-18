/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_MAX_ARITY_HPP
#define CALLABLE_TRAITS_MAX_ARITY_HPP

#include <callable_traits/detail/arity.hpp>
#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/required_definitions.hpp>
#include <utility>

namespace callable_traits {

    template<typename T, std::size_t SearchLimit = constants::arity_search_limit>
    inline constexpr auto
    max_arity() {

#ifdef CALLABLE_TRAITS_DISABLE_ARITY_RANGE
        return detail::arity_t<detail::traits<T>>{};
#else
        return detail::max_arity_t<detail::traits<T>, SearchLimit>{};
#endif

    }

    template<std::size_t SearchLimit = constants::arity_search_limit, typename T>
    inline constexpr auto
    max_arity(T&&) {
        using no_ref = typename std::remove_reference<T>::type;
        return max_arity<no_ref, SearchLimit>();
    }
}

#endif
