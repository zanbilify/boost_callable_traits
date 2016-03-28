/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DISJUNCTION_HPP
#define CALLABLE_TRAITS_DISJUNCTION_HPP

#include <type_traits>

namespace callable_traits {

    namespace detail {

        template<typename...>
        struct disjunction
            : std::false_type {};

        template<typename T>
        struct disjunction<T>
            : T {};

        template<typename T, typename... Ts>
        struct disjunction<T, Ts...>
            : std::conditional<T::value != false, T, disjunction<Ts...>>::type { };
    }
}

#endif
