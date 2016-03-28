/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FLAG_MAP_HPP
#define CALLABLE_TRAITS_FLAG_MAP_HPP

#include <callable_traits/flags.hpp>

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct flag_map {
            static_assert(sizeof(T) < 0,
                "Invalid argument passed to flag_map template.");

            static constexpr flags value = default_;
        };

        template<> struct flag_map<int> { static constexpr flags value = default_; };
        template<> struct flag_map<int &> { static constexpr flags value = lref_; };
        template<> struct flag_map<int &&> { static constexpr flags value = rref_; };
        template<> struct flag_map<int const> { static constexpr flags value = const_; };
        template<> struct flag_map<int const &> { static constexpr flags value = const_ | lref_; };
        template<> struct flag_map<int const &&> { static constexpr flags value = const_ | rref_; };
        template<> struct flag_map<int volatile> { static constexpr flags value = volatile_; };
        template<> struct flag_map<int volatile &> { static constexpr flags value = volatile_ | lref_; };
        template<> struct flag_map<int volatile &&> { static constexpr flags value = volatile_ | rref_; };
        template<> struct flag_map<int const volatile> { static constexpr flags value = const_ | volatile_; };
        template<> struct flag_map<int const volatile &> { static constexpr flags value = const_ | volatile_ | lref_; };
        template<> struct flag_map<int const volatile &&> { static constexpr flags value = const_ | volatile_ | rref_; };
    }
}

#endif